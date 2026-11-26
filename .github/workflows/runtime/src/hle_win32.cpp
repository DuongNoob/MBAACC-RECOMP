#include "mbaa_recomp/hle_win32.h"
#include "mbaa_recomp/d3d9_shim.h"
#include "mbaa_recomp/dispatch.h"
#include "mbaa_recomp/hle_audio.h"
#include "mbaa_recomp/hle_input.h"

#if defined(__APPLE__)
#import <CoreFoundation/CoreFoundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreText/CoreText.h>
extern "C" void* objc_autoreleasePoolPush(void);
extern "C" void  objc_autoreleasePoolPop(void* pool);
#endif

#if !defined(_WIN32)
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cctype>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <filesystem>
#include <fstream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

namespace mbaa_recomp {

// Bridge callback hook wired by RuntimeEngine::init() to D3D9MetalBridge
namespace detail {
static std::atomic<D3DIatHandlerFn> g_d3d_iat_handler{nullptr};
} // namespace detail

void hle_win32_register_d3d_handler(D3DIatHandlerFn fn) {
    detail::g_d3d_iat_handler.store(fn, std::memory_order_release);
}

#if !defined(__APPLE__)
// Non-Apple host build fallbacks so portable CMake library links cleanly without .mm sources.
void hle_direct_input8_create(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 0x80004005u;
    ctx.ret_stdcall(mem, 20u);
}
int16_t input_get_vk_state(int /*vk_code*/) { return 0; }
void hle_direct_sound_create8(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 0x80004005u;
    ctx.ret_stdcall(mem, 12u);
}
#endif

namespace {

// Win32 status & constants
constexpr uint32_t kINVALID_HANDLE_VALUE    = 0xFFFFFFFFu;
constexpr uint32_t kINVALID_FILE_ATTRIBUTES = 0xFFFFFFFFu;
constexpr uint32_t kFILE_ATTRIBUTE_DIRECTORY= 0x00000010u;
constexpr uint32_t kFILE_ATTRIBUTE_NORMAL   = 0x00000080u;
constexpr uint32_t kERROR_FILE_NOT_FOUND    = 2u;
constexpr uint32_t kERROR_PATH_NOT_FOUND    = 3u;
constexpr uint32_t kERROR_INVALID_HANDLE    = 6u;
constexpr uint32_t kERROR_INVALID_PARAMETER = 87u;
constexpr uint32_t kERROR_ALREADY_EXISTS    = 183u;
constexpr uint32_t kERROR_NO_MORE_FILES     = 18u;
constexpr uint32_t kWAIT_OBJECT_0           = 0x00000000u;
constexpr uint32_t kWAIT_IO_COMPLETION      = 0x000000C0u;
constexpr uint32_t kWAIT_TIMEOUT            = 0x00000102u;
constexpr uint32_t kWAIT_FAILED             = 0xFFFFFFFFu;
constexpr uint32_t kWM_QUIT                 = 0x0012u;
constexpr uint32_t kIDOK                    = 1u;
constexpr uint32_t kHWND_MAIN               = 0x10000001u;
constexpr uint32_t kHDC_MAIN                = 0x10000002u;
constexpr uint32_t kHMENU_MAIN              = 0x10000003u;
constexpr uint32_t kHINST_MAIN              = 0x00400000u;

struct GuestThreadExit {
    uint32_t code = 0u;
};

struct PendingApc {
    uint32_t fn_va = 0u;
    uint32_t dw_error = 0u;
    uint32_t cb_transferred = 0u;
    uint32_t lp_overlapped = 0u;
    uint32_t dw_flags = 0u;
};

struct SyncEvent {
    bool manual_reset = false;
    bool signaled     = false;
    std::mutex mtx;
    std::condition_variable cv;
};

struct SyncMutex {
    std::mutex mtx;
    std::condition_variable cv;
    bool owned = false;
    std::thread::id owner{};
    uint32_t recursion = 0;
};

struct SyncSemaphore {
    std::mutex mtx;
    std::condition_variable cv;
    int32_t count = 0;
    int32_t max_count = 1;
};

struct ThreadMessage {
    uint32_t hwnd    = 0;
    uint32_t message = 0;
    uint32_t wparam  = 0;
    uint32_t lparam  = 0;
    uint32_t time_ms = 0;
};

struct SyncThread {
    uint32_t tid = 0;
    std::atomic<uint32_t> exit_code{0};
    std::shared_ptr<SyncEvent> done_event = std::make_shared<SyncEvent>();
};

struct FindEntry {
    std::string name;
    bool is_dir = false;
    uint64_t size = 0;
    uint64_t mtime_filetime = 130000000000000000ULL;
};

struct FindState {
    std::vector<FindEntry> entries;
    size_t index = 0;
};

struct FileState {
    std::mutex mtx;
    std::FILE* fp = nullptr;
    std::string path;
    bool writable = false;
    uint32_t last_bytes_read = 0;
};

struct FontState {
    int32_t height = 16;
    int32_t weight = 400;
    std::string face = "MS Gothic";
};

enum class HandleKind {
    None,
    File,
    Find,
    Event,
    Mutex,
    Semaphore,
    Thread,
    GlobalMem,
    Font,
};

struct HandleRecord {
    HandleKind kind = HandleKind::None;
    std::shared_ptr<FileState> file;
    std::shared_ptr<FindState> find;
    std::shared_ptr<SyncEvent> event;
    std::shared_ptr<SyncMutex> mutex;
    std::shared_ptr<SyncSemaphore> sem;
    std::shared_ptr<SyncThread> thread;
    std::shared_ptr<FontState> font;
    uint32_t guest_ptr = 0;
};

struct ThreadQueue {
    std::mutex mtx;
    std::deque<ThreadMessage> msgs;
};

struct Win32State {
    std::mutex state_mtx;
    std::string assets_dir;
    uint32_t screen_w = 640u;
    uint32_t screen_h = 480u;
    std::chrono::steady_clock::time_point boot_time = std::chrono::steady_clock::now();

    std::atomic<uint32_t> next_handle{0x20000010u};
    std::atomic<uint32_t> next_tid{2u};
    std::unordered_map<uint32_t, HandleRecord> handles;
    std::unordered_map<std::string, uint32_t> named_mutexes;
    std::unordered_map<uint32_t, std::shared_ptr<std::recursive_mutex>> crit_sections;
    std::unordered_map<uint32_t, std::shared_ptr<ThreadQueue>> thread_queues;
    std::unordered_map<uint32_t, uint32_t> window_longs;
    std::unordered_map<uint32_t, uint32_t> selected_font_by_dc;
    std::vector<std::string> clipboard_text;

    std::atomic<bool> quit_requested{false};
    std::atomic<int> quit_code{0};
    std::thread::id main_thread_id;
    std::function<bool()> frame_yield_cb;
    std::mutex worker_mtx;
    std::condition_variable worker_cv;
    int active_workers = 0;
    std::mutex interlocked_mtx;

    std::atomic<uint32_t> next_tls{0u};
    std::array<bool, 64> tls_used{};
    std::atomic<int32_t> last_wsa_error{0};
    std::string wsa_ntoa_buf;
    uint32_t hostent_va = 0;
    uint32_t env_ansi_va = 0;
    uint32_t env_wide_va = 0;
    uint32_t cmdline_va = 0;
    uint32_t temp_str_va = 0;
};

Win32State g_w32;
thread_local uint32_t tls_last_error = 0u;
thread_local uint32_t tls_tid = 0u;
thread_local bool tls_is_worker = false;
thread_local std::array<uint32_t, 64> tls_values{};
thread_local std::deque<PendingApc> tls_pending_apcs;

bool dispatch_pending_apcs(CpuContext& ctx, GuestMemory& mem) {
    const size_t count = tls_pending_apcs.size();
    if (count == 0u) return false;
    for (size_t i = 0; i < count; ++i) {
        if (tls_pending_apcs.empty()) break;
        if (g_w32.quit_requested.load(std::memory_order_acquire)) {
            tls_pending_apcs.clear();
            break;
        }
        const PendingApc apc = tls_pending_apcs.front();
        tls_pending_apcs.pop_front();
        if (apc.fn_va == 0u) continue;

        const uint32_t saved_ebx = ctx.ebx;
        const uint32_t saved_esi = ctx.esi;
        const uint32_t saved_edi = ctx.edi;
        const uint32_t saved_ebp = ctx.ebp;
        const uint32_t saved_esp = ctx.esp;

        // LPWSAOVERLAPPED_COMPLETION_ROUTINE(dwError, cbTransferred, lpOverlapped, dwFlags) [stdcall]
        ctx.push32(mem, apc.dw_flags);
        ctx.push32(mem, apc.lp_overlapped);
        ctx.push32(mem, apc.cb_transferred);
        ctx.push32(mem, apc.dw_error);
        ctx.push32(mem, 0x00FFFFF4u); // Sentinel return EIP
        call_indirect(ctx, mem, apc.fn_va);

        ctx.esp = saved_esp;
        ctx.ebx = saved_ebx;
        ctx.esi = saved_esi;
        ctx.edi = saved_edi;
        ctx.ebp = saved_ebp;
    }
    return true;
}

void wake_all_sync_waiters() {
    std::vector<std::shared_ptr<SyncEvent>> events;
    std::vector<std::shared_ptr<SyncMutex>> mutexes;
    std::vector<std::shared_ptr<SyncSemaphore>> sems;
    {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        for (const auto& kv : g_w32.handles) {
            const auto& r = kv.second;
            if (r.kind == HandleKind::Event && r.event) {
                events.push_back(r.event);
            } else if (r.kind == HandleKind::Thread && r.thread && r.thread->done_event) {
                events.push_back(r.thread->done_event);
            } else if (r.kind == HandleKind::Mutex && r.mutex) {
                mutexes.push_back(r.mutex);
            } else if (r.kind == HandleKind::Semaphore && r.sem) {
                sems.push_back(r.sem);
            }
        }
    }
    for (auto& ev : events) {
        std::lock_guard<std::mutex> lk(ev->mtx);
        ev->cv.notify_all();
    }
    for (auto& mx : mutexes) {
        std::lock_guard<std::mutex> lk(mx->mtx);
        mx->cv.notify_all();
    }
    for (auto& sm : sems) {
        std::lock_guard<std::mutex> lk(sm->mtx);
        sm->cv.notify_all();
    }
}

uint32_t current_tid() {
    if (tls_tid == 0u) {
        if (std::this_thread::get_id() == g_w32.main_thread_id) {
            tls_tid = 1u;
        } else {
            tls_tid = g_w32.next_tid.fetch_add(1u, std::memory_order_relaxed);
        }
    }
    return tls_tid;
}

std::shared_ptr<ThreadQueue> get_thread_queue(uint32_t tid) {
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    auto& q = g_w32.thread_queues[tid];
    if (!q) q = std::make_shared<ThreadQueue>();
    return q;
}

uint32_t insert_handle(HandleRecord rec) {
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    const uint32_t h = g_w32.next_handle.fetch_add(1u, std::memory_order_relaxed);
    g_w32.handles[h] = std::move(rec);
    return h;
}

bool get_handle(uint32_t h, HandleRecord& out) {
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    auto it = g_w32.handles.find(h);
    if (it == g_w32.handles.end()) return false;
    out = it->second;
    return true;
}

uint32_t tick_ms() {
    const auto now = std::chrono::steady_clock::now();
    return static_cast<uint32_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now - g_w32.boot_time).count());
}

struct DebugLogState {
    std::mutex mtx;
    std::FILE* fp = nullptr;
    std::deque<std::string> ring;
    uint32_t lines_written = 0;
    std::atomic<uint32_t> missing_file_logs{0};
    std::atomic<uint32_t> found_file_logs{0};
    std::atomic<uint32_t> thread_spawn_count{0};
    std::atomic<uint32_t> thread_fail_count{0};
    std::atomic<uint32_t> destroy_window_calls{0};
    std::atomic<uint32_t> dialog_box_calls{0};
    std::atomic<int32_t>  cursor_display_count{0};
};

DebugLogState g_log;

void append_debug_log_line(const char* text) {
    if (!text) return;
    char prefix[32] = {};
    std::snprintf(prefix, sizeof(prefix), "[%ums] ", tick_ms());
    std::string line = std::string(prefix) + text;
    std::fprintf(stderr, "%s\n", line.c_str());

    std::lock_guard<std::mutex> lock(g_log.mtx);
    g_log.ring.push_back(line);
    while (g_log.ring.size() > 32u) {
        g_log.ring.pop_front();
    }
    if (g_log.fp != nullptr && g_log.lines_written < 2500u) {
        std::fwrite(line.data(), 1u, line.size(), g_log.fp);
        std::fputc('\n', g_log.fp);
        std::fflush(g_log.fp);
        ++g_log.lines_written;
    }
}

std::string ascii_lower(std::string s) {
    for (char& ch : s) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return s;
}

std::vector<std::string> split_win_path(const std::string& raw) {
    std::string p = raw;
    std::replace(p.begin(), p.end(), '\\', '/');
    // Strip Windows drive prefix e.g. C:/
    if (p.size() >= 2 && std::isalpha(static_cast<unsigned char>(p[0])) && p[1] == ':') {
        p = p.substr(2);
    }
    std::vector<std::string> parts;
    std::stringstream ss(p);
    std::string item;
    while (std::getline(ss, item, '/')) {
        if (item.empty() || item == ".") continue;
        if (item == "..") {
            if (!parts.empty()) parts.pop_back();
            continue;
        }
        parts.push_back(item);
    }
    return parts;
}

/// Resolves a Windows relative/asset path case-insensitively inside `g_w32.assets_dir`.
fs::path resolve_asset_path(const std::string& win_path, bool for_write, bool* exists_out = nullptr) {
    (void)for_write;
    if (exists_out) *exists_out = false;
    if (g_w32.assets_dir.empty()) return {};

    std::error_code ec;
    fs::path root(g_w32.assets_dir);
    std::string rel_path = win_path;

    // If an already-rooted POSIX path inside assets_dir was passed (e.g. derived from
    // GetModuleFileNameA + appended Windows subdirs), strip the assets_dir prefix so
    // backslashes and case-insensitive segment matching still run on the suffix.
    if (!rel_path.empty() && rel_path[0] == '/' &&
        rel_path.rfind(g_w32.assets_dir, 0) == 0) {
        const size_t base_len = g_w32.assets_dir.size();
        if (rel_path.size() == base_len) {
            ec.clear();
            const bool ex = fs::exists(root, ec) && !ec;
            if (exists_out) *exists_out = ex;
            return root;
        }
        const char sep = rel_path[base_len];
        if (sep == '/' || sep == '\\') {
            rel_path = rel_path.substr(base_len + 1u);
        }
    }

    const auto parts = split_win_path(rel_path);
    fs::path cur = root;
    for (size_t i = 0; i < parts.size(); ++i) {
        const std::string& seg = parts[i];
        bool matched = false;

        // Fast-path exact-case lookup before scanning the directory.
        const fs::path direct = cur / seg;
        ec.clear();
        if (fs::exists(direct, ec) && !ec) {
            cur = direct;
            matched = true;
        } else {
            ec.clear();
            const bool cur_is_dir = fs::exists(cur, ec) && !ec && fs::is_directory(cur, ec) && !ec;
            if (cur_is_dir) {
                const std::string seg_low = ascii_lower(seg);
                ec.clear();
                for (fs::directory_iterator it(cur, ec), end; !ec && it != end; it.increment(ec)) {
                    const std::string fname = it->path().filename().string();
                    if (ascii_lower(fname) == seg_low) {
                        cur /= fname;
                        matched = true;
                        break;
                    }
                }
            }
        }

        if (!matched) {
            // Preserve the full remaining normalized path instead of truncating at the first missing parent.
            for (size_t j = i; j < parts.size(); ++j) {
                cur /= parts[j];
            }
            if (exists_out) *exists_out = false;
            return cur;
        }
    }

    ec.clear();
    if (exists_out) *exists_out = fs::exists(cur, ec) && !ec;
    return cur;
}

uint64_t to_win_filetime(const fs::file_time_type& ft) {
    (void)ft;
    return 130000000000000000ULL;
}

bool wildcard_match_ci(const std::string& pat, const std::string& name) {
    const std::string p = ascii_lower(pat);
    const std::string s = ascii_lower(name);
    if (p == "*.*" || p == "*") return true;
    size_t pi = 0, si = 0, star = std::string::npos, match = 0;
    while (si < s.size()) {
        if (pi < p.size() && (p[pi] == '?' || p[pi] == s[si])) {
            ++pi; ++si;
        } else if (pi < p.size() && p[pi] == '*') {
            star = pi++;
            match = si;
        } else if (star != std::string::npos) {
            pi = star + 1;
            si = ++match;
        } else {
            return false;
        }
    }
    while (pi < p.size() && p[pi] == '*') ++pi;
    return pi == p.size();
}

// ---------------------------------------------------------------------------
// Codepage conversion (Shift-JIS CP932 <-> UTF-16)
// ---------------------------------------------------------------------------
std::vector<uint16_t> decode_to_utf16(uint32_t codepage, const char* src, int src_len) {
    std::vector<uint16_t> out;
    if (!src) return out;
    size_t n = (src_len < 0) ? (std::strlen(src) + 1u) : static_cast<size_t>(src_len);
    if (n == 0u) return out;

#if defined(__APPLE__)
    CFStringEncoding enc = kCFStringEncodingDOSJapanese;
    if (codepage == 65001u) enc = kCFStringEncodingUTF8;
    else if (codepage == 1252u) enc = kCFStringEncodingWindowsLatin1;
    else if (codepage == 20127u) enc = kCFStringEncodingASCII;

    const bool has_nul = (src_len < 0) || (n > 0 && src[n - 1] == '\0');
    const size_t body_n = has_nul ? (n - 1u) : n;
    CFStringRef cf = CFStringCreateWithBytes(
        kCFAllocatorDefault, reinterpret_cast<const UInt8*>(src),
        static_cast<CFIndex>(body_n), enc, false);
    if (!cf && enc != kCFStringEncodingUTF8) {
        cf = CFStringCreateWithBytes(
            kCFAllocatorDefault, reinterpret_cast<const UInt8*>(src),
            static_cast<CFIndex>(body_n), kCFStringEncodingUTF8, false);
    }
    if (cf) {
        const CFIndex len = CFStringGetLength(cf);
        out.resize(static_cast<size_t>(len));
        if (len > 0) {
            CFStringGetCharacters(cf, CFRangeMake(0, len), reinterpret_cast<UniChar*>(out.data()));
        }
        CFRelease(cf);
        if (has_nul) out.push_back(0u);
        return out;
    }
#else
    (void)codepage;
#endif
    for (size_t i = 0; i < n; ++i) {
        out.push_back(static_cast<uint8_t>(src[i]));
    }
    return out;
}

std::vector<uint8_t> encode_from_utf16(uint32_t codepage, const uint16_t* src, int src_chars) {
    std::vector<uint8_t> out;
    if (!src) return out;
    size_t n = 0;
    if (src_chars < 0) {
        while (src[n] != 0u) ++n;
        ++n;
    } else {
        n = static_cast<size_t>(src_chars);
    }
    if (n == 0u) return out;

#if defined(__APPLE__)
    CFStringEncoding enc = kCFStringEncodingDOSJapanese;
    if (codepage == 65001u) enc = kCFStringEncodingUTF8;
    else if (codepage == 1252u) enc = kCFStringEncodingWindowsLatin1;

    const bool has_nul = (src_chars < 0) || (n > 0 && src[n - 1] == 0u);
    const size_t body_n = has_nul ? (n - 1u) : n;
    CFStringRef cf = CFStringCreateWithCharacters(
        kCFAllocatorDefault, reinterpret_cast<const UniChar*>(src), static_cast<CFIndex>(body_n));
    if (cf) {
        CFIndex used = 0;
        const CFRange rng = CFRangeMake(0, static_cast<CFIndex>(body_n));
        if (CFStringGetBytes(cf, rng, enc, '?', false, nullptr, 0, &used) == static_cast<CFIndex>(body_n) || used > 0) {
            out.resize(static_cast<size_t>(used));
            CFStringGetBytes(cf, rng, enc, '?', false, out.data(), used, &used);
        }
        CFRelease(cf);
        if (has_nul) out.push_back(0u);
        return out;
    }
#else
    (void)codepage;
#endif
    for (size_t i = 0; i < n; ++i) {
        out.push_back(static_cast<uint8_t>(src[i] & 0x7Fu));
    }
    return out;
}

// ---------------------------------------------------------------------------
// Synchronized wait helpers
// ---------------------------------------------------------------------------
uint32_t wait_single_handle(uint32_t h, uint32_t timeout_ms) {
    if (h == 0u || h == kINVALID_HANDLE_VALUE) {
        tls_last_error = kERROR_INVALID_HANDLE;
        return kWAIT_FAILED;
    }
    HandleRecord rec;
    if (!get_handle(h, rec)) {
        tls_last_error = kERROR_INVALID_HANDLE;
        return kWAIT_FAILED;
    }

    auto calc_deadline = [timeout_ms]() {
        return std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);
    };
    auto is_quitting = []() {
        return g_w32.quit_requested.load(std::memory_order_acquire);
    };

    if (rec.kind == HandleKind::Thread && rec.thread) {
        rec.event = rec.thread->done_event;
        rec.kind = HandleKind::Event;
    }

    if (rec.kind == HandleKind::Event && rec.event) {
        std::unique_lock<std::mutex> lock(rec.event->mtx);
        auto pred = [&]() { return rec.event->signaled || is_quitting(); };
        if (!pred()) {
            if (timeout_ms == 0u) return kWAIT_TIMEOUT;
            if (timeout_ms == 0xFFFFFFFFu) {
                rec.event->cv.wait(lock, pred);
            } else if (!rec.event->cv.wait_until(lock, calc_deadline(), pred)) {
                return kWAIT_TIMEOUT;
            }
        }
        if (!rec.event->signaled && is_quitting()) {
            if (tls_is_worker) throw GuestThreadExit{0u};
            return kWAIT_OBJECT_0;
        }
        if (!rec.event->manual_reset) {
            rec.event->signaled = false;
        }
        return kWAIT_OBJECT_0;
    }

    if (rec.kind == HandleKind::Mutex && rec.mutex) {
        const auto me = std::this_thread::get_id();
        std::unique_lock<std::mutex> lock(rec.mutex->mtx);
        auto pred = [&]() { return !rec.mutex->owned || rec.mutex->owner == me || is_quitting(); };
        if (!pred()) {
            if (timeout_ms == 0u) return kWAIT_TIMEOUT;
            if (timeout_ms == 0xFFFFFFFFu) {
                rec.mutex->cv.wait(lock, pred);
            } else if (!rec.mutex->cv.wait_until(lock, calc_deadline(), pred)) {
                return kWAIT_TIMEOUT;
            }
        }
        if (rec.mutex->owned && rec.mutex->owner != me && is_quitting()) {
            if (tls_is_worker) throw GuestThreadExit{0u};
            return kWAIT_OBJECT_0;
        }
        rec.mutex->owned = true;
        rec.mutex->owner = me;
        rec.mutex->recursion++;
        return kWAIT_OBJECT_0;
    }

    if (rec.kind == HandleKind::Semaphore && rec.sem) {
        std::unique_lock<std::mutex> lock(rec.sem->mtx);
        auto pred = [&]() { return rec.sem->count > 0 || is_quitting(); };
        if (!pred()) {
            if (timeout_ms == 0u) return kWAIT_TIMEOUT;
            if (timeout_ms == 0xFFFFFFFFu) {
                rec.sem->cv.wait(lock, pred);
            } else if (!rec.sem->cv.wait_until(lock, calc_deadline(), pred)) {
                return kWAIT_TIMEOUT;
            }
        }
        if (rec.sem->count <= 0 && is_quitting()) {
            if (tls_is_worker) throw GuestThreadExit{0u};
            return kWAIT_OBJECT_0;
        }
        rec.sem->count--;
        return kWAIT_OBJECT_0;
    }

    return kWAIT_OBJECT_0;
}

// ---------------------------------------------------------------------------
// KERNEL32 Shims
// ---------------------------------------------------------------------------
void k32_get_last_error(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = tls_last_error;
    ctx.ret_stdcall(mem, 0u);
}

void k32_set_last_error(CpuContext& ctx, GuestMemory& mem) {
    tls_last_error = ctx.arg32(mem, 0);
    ctx.ret_stdcall(mem, 4u);
}

void k32_create_file_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t name_va = ctx.arg32(mem, 0);
    const uint32_t access  = ctx.arg32(mem, 1);
    const uint32_t disp    = ctx.arg32(mem, 4);

    const std::string raw_name = mem.read_cstring(name_va);
    const bool want_write = (access & 0x40000000u) != 0u;
    const bool create_new = (disp == 1u /*CREATE_NEW*/ || disp == 2u /*CREATE_ALWAYS*/ || disp == 4u /*OPEN_ALWAYS*/);

    bool exists = false;
    const fs::path resolved = resolve_asset_path(raw_name, want_write || create_new, &exists);
    if (resolved.empty() || (!exists && !create_new)) {
        const uint32_t n = g_log.missing_file_logs.fetch_add(1u, std::memory_order_relaxed);
        if (n < 40u) {
            hle_win32_log("CreateFileA MISS #%u: '%s' -> '%s'",
                          n + 1u, raw_name.c_str(), resolved.string().c_str());
        }
        tls_last_error = kERROR_FILE_NOT_FOUND;
        ctx.eax = kINVALID_HANDLE_VALUE;
        ctx.ret_stdcall(mem, 28u);
        return;
    }

    if (create_new && resolved.has_parent_path()) {
        std::error_code ec;
        fs::create_directories(resolved.parent_path(), ec);
    }

    const char* mode = "rb";
    if (want_write) {
        mode = (disp == 2u /*CREATE_ALWAYS*/) ? "wb+" : (exists ? "rb+" : "wb+");
    }

    std::FILE* fp = std::fopen(resolved.string().c_str(), mode);
    if (!fp) {
        const uint32_t n = g_log.missing_file_logs.fetch_add(1u, std::memory_order_relaxed);
        if (n < 40u) {
            hle_win32_log("CreateFileA FOPEN ERR #%u: '%s' -> '%s'",
                          n + 1u, raw_name.c_str(), resolved.string().c_str());
        }
        tls_last_error = kERROR_FILE_NOT_FOUND;
        ctx.eax = kINVALID_HANDLE_VALUE;
        ctx.ret_stdcall(mem, 28u);
        return;
    }

    const std::string low = ascii_lower(raw_name);
    if (low.find(".p") != std::string::npos ||
        low.find(".cfx") != std::string::npos ||
        low.find(".ini") != std::string::npos) {
        const uint32_t fn = g_log.found_file_logs.fetch_add(1u, std::memory_order_relaxed);
        if (fn < 25u) {
            hle_win32_log("CreateFileA OK #%u: '%s'", fn + 1u, raw_name.c_str());
        }
    }

    auto fst = std::make_shared<FileState>();
    fst->fp = fp;
    fst->path = resolved.string();
    fst->writable = want_write;

    HandleRecord rec;
    rec.kind = HandleKind::File;
    rec.file = fst;
    tls_last_error = (exists && (disp == 2u || disp == 4u)) ? kERROR_ALREADY_EXISTS : 0u;
    ctx.eax = insert_handle(std::move(rec));
    ctx.ret_stdcall(mem, 28u);
}

void k32_read_file(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h          = ctx.arg32(mem, 0);
    const uint32_t buf_va     = ctx.arg32(mem, 1);
    const uint32_t to_read    = ctx.arg32(mem, 2);
    const uint32_t bytes_va   = ctx.arg32(mem, 3);
    const uint32_t ovl_va     = ctx.arg32(mem, 4);

    HandleRecord rec;
    if (!get_handle(h, rec) || rec.kind != HandleKind::File || !rec.file || !rec.file->fp) {
        tls_last_error = kERROR_INVALID_HANDLE;
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 20u);
        return;
    }

    uint8_t* dst = mem.ptr(buf_va);
    if (!dst || !mem.in_bounds(buf_va, to_read)) {
        tls_last_error = kERROR_INVALID_PARAMETER;
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 20u);
        return;
    }

    size_t n = 0u;
    {
        std::lock_guard<std::mutex> flk(rec.file->mtx);
        if (ovl_va != 0u) {
            const uint64_t offset = static_cast<uint64_t>(mem.r32(ovl_va + 8u)) |
                                    (static_cast<uint64_t>(mem.r32(ovl_va + 12u)) << 32);
#if !defined(_WIN32)
            ::fseeko(rec.file->fp, static_cast<off_t>(offset), SEEK_SET);
#else
            ::_fseeki64(rec.file->fp, static_cast<int64_t>(offset), SEEK_SET);
#endif
        }
        n = (to_read > 0u) ? std::fread(dst, 1u, to_read, rec.file->fp) : 0u;
        rec.file->last_bytes_read = static_cast<uint32_t>(n);
    }

    if (bytes_va != 0u) mem.w32(bytes_va, static_cast<uint32_t>(n));
    if (ovl_va != 0u) {
        mem.w32(ovl_va + 0u, 0u); // Internal = STATUS_SUCCESS
        mem.w32(ovl_va + 4u, static_cast<uint32_t>(n)); // InternalHigh = bytes transferred
        const uint32_t ev = mem.r32(ovl_va + 16u);
        if (ev) hle_win32_signal_event(ev);
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 20u);
}

void k32_get_overlapped_result(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h       = ctx.arg32(mem, 0);
    const uint32_t ovl_va  = ctx.arg32(mem, 1);
    const uint32_t xfer_va = ctx.arg32(mem, 2);

    uint32_t transferred = 0u;
    if (ovl_va != 0u && mem.in_bounds(ovl_va, 8u)) {
        transferred = mem.r32(ovl_va + 4u);
    }
    if (transferred == 0u) {
        HandleRecord rec;
        if (get_handle(h, rec) && rec.kind == HandleKind::File && rec.file) {
            std::lock_guard<std::mutex> flk(rec.file->mtx);
            transferred = rec.file->last_bytes_read;
        }
    }
    if (xfer_va != 0u && mem.in_bounds(xfer_va, 4u)) {
        mem.w32(xfer_va, transferred);
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 16u);
}

void k32_write_file(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h        = ctx.arg32(mem, 0);
    const uint32_t buf_va   = ctx.arg32(mem, 1);
    const uint32_t to_write = ctx.arg32(mem, 2);
    const uint32_t bytes_va = ctx.arg32(mem, 3);

    HandleRecord rec;
    if (!get_handle(h, rec) || rec.kind != HandleKind::File || !rec.file || !rec.file->fp) {
        tls_last_error = kERROR_INVALID_HANDLE;
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 20u);
        return;
    }

    const uint8_t* src = mem.ptr(buf_va);
    if (!src || !mem.in_bounds(buf_va, to_write)) {
        tls_last_error = kERROR_INVALID_PARAMETER;
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 20u);
        return;
    }

    size_t n = 0u;
    {
        std::lock_guard<std::mutex> flk(rec.file->mtx);
        n = (to_write > 0u) ? std::fwrite(src, 1u, to_write, rec.file->fp) : 0u;
        std::fflush(rec.file->fp);
    }
    if (bytes_va != 0u) mem.w32(bytes_va, static_cast<uint32_t>(n));
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 20u);
}

void k32_set_file_pointer(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h      = ctx.arg32(mem, 0);
    const int32_t  dist   = static_cast<int32_t>(ctx.arg32(mem, 1));
    const uint32_t hi_va  = ctx.arg32(mem, 2);
    const uint32_t method = ctx.arg32(mem, 3);

    HandleRecord rec;
    if (!get_handle(h, rec) || rec.kind != HandleKind::File || !rec.file || !rec.file->fp) {
        tls_last_error = kERROR_INVALID_HANDLE;
        ctx.eax = 0xFFFFFFFFu;
        ctx.ret_stdcall(mem, 16u);
        return;
    }

    int whence = SEEK_SET;
    if (method == 1u) whence = SEEK_CUR;
    else if (method == 2u) whence = SEEK_END;

    int64_t full = dist;
    if (hi_va != 0u) {
        const int32_t hi = static_cast<int32_t>(mem.r32(hi_va));
        full = (static_cast<int64_t>(hi) << 32) | static_cast<uint32_t>(dist);
    }

    int64_t pos = 0;
    {
        std::lock_guard<std::mutex> flk(rec.file->mtx);
#if !defined(_WIN32)
        ::fseeko(rec.file->fp, static_cast<off_t>(full), whence);
        pos = static_cast<int64_t>(::ftello(rec.file->fp));
#else
        ::_fseeki64(rec.file->fp, full, whence);
        pos = ::_ftelli64(rec.file->fp);
#endif
    }
    if (hi_va != 0u) {
        mem.w32(hi_va, static_cast<uint32_t>(static_cast<uint64_t>(pos) >> 32));
    }
    ctx.eax = static_cast<uint32_t>(pos & 0xFFFFFFFFu);
    ctx.ret_stdcall(mem, 16u);
}

void k32_get_file_size(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h     = ctx.arg32(mem, 0);
    const uint32_t hi_va = ctx.arg32(mem, 1);

    HandleRecord rec;
    if (!get_handle(h, rec) || rec.kind != HandleKind::File || !rec.file || !rec.file->fp) {
        tls_last_error = kERROR_INVALID_HANDLE;
        ctx.eax = 0xFFFFFFFFu;
        ctx.ret_stdcall(mem, 8u);
        return;
    }

    int64_t sz = 0;
    {
        std::lock_guard<std::mutex> flk(rec.file->mtx);
#if !defined(_WIN32)
        const off_t cur = ::ftello(rec.file->fp);
        ::fseeko(rec.file->fp, 0, SEEK_END);
        sz = static_cast<int64_t>(::ftello(rec.file->fp));
        ::fseeko(rec.file->fp, cur, SEEK_SET);
#else
        const int64_t cur = ::_ftelli64(rec.file->fp);
        ::_fseeki64(rec.file->fp, 0, SEEK_END);
        sz = ::_ftelli64(rec.file->fp);
        ::_fseeki64(rec.file->fp, cur, SEEK_SET);
#endif
    }
    if (hi_va != 0u) mem.w32(hi_va, static_cast<uint32_t>(static_cast<uint64_t>(sz) >> 32));
    ctx.eax = static_cast<uint32_t>(sz & 0xFFFFFFFFu);
    ctx.ret_stdcall(mem, 8u);
}

void k32_get_file_attributes_a(CpuContext& ctx, GuestMemory& mem) {
    const std::string raw = mem.read_cstring(ctx.arg32(mem, 0));
    bool exists = false;
    const fs::path p = resolve_asset_path(raw, false, &exists);
    if (!exists) {
        tls_last_error = kERROR_FILE_NOT_FOUND;
        ctx.eax = kINVALID_FILE_ATTRIBUTES;
    } else {
        std::error_code ec;
        ctx.eax = fs::is_directory(p, ec) ? kFILE_ATTRIBUTE_DIRECTORY : kFILE_ATTRIBUTE_NORMAL;
    }
    ctx.ret_stdcall(mem, 4u);
}

void k32_create_directory_a(CpuContext& ctx, GuestMemory& mem) {
    const std::string raw = mem.read_cstring(ctx.arg32(mem, 0));
    const fs::path p = resolve_asset_path(raw, true);
    std::error_code ec;
    const bool ok = !p.empty() && (fs::exists(p, ec) || fs::create_directories(p, ec));
    ctx.eax = ok ? 1u : 0u;
    ctx.ret_stdcall(mem, 8u);
}

void k32_delete_file_a(CpuContext& ctx, GuestMemory& mem) {
    const std::string raw = mem.read_cstring(ctx.arg32(mem, 0));
    bool exists = false;
    const fs::path p = resolve_asset_path(raw, false, &exists);
    std::error_code ec;
    ctx.eax = (exists && fs::remove(p, ec)) ? 1u : 0u;
    ctx.ret_stdcall(mem, 4u);
}

void write_find_data_a(GuestMemory& mem, uint32_t fd_va, const FindEntry& e) {
    mem.zero_bytes(fd_va, 320u);
    mem.w32(fd_va + 0u, e.is_dir ? kFILE_ATTRIBUTE_DIRECTORY : kFILE_ATTRIBUTE_NORMAL);
    mem.w32(fd_va + 20u, static_cast<uint32_t>(e.mtime_filetime & 0xFFFFFFFFu));
    mem.w32(fd_va + 24u, static_cast<uint32_t>(e.mtime_filetime >> 32));
    mem.w32(fd_va + 28u, static_cast<uint32_t>(e.size >> 32));
    mem.w32(fd_va + 32u, static_cast<uint32_t>(e.size & 0xFFFFFFFFu));
    mem.write_cstring(fd_va + 44u, e.name, 260u);
}

void k32_find_first_file_a(CpuContext& ctx, GuestMemory& mem) {
    const std::string raw_pat = mem.read_cstring(ctx.arg32(mem, 0));
    const uint32_t fd_va      = ctx.arg32(mem, 1);

    auto parts = split_win_path(raw_pat);
    const std::string pat = parts.empty() ? "*" : parts.back();
    if (!parts.empty()) parts.pop_back();

    std::string dir_rel;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) dir_rel.push_back('/');
        dir_rel += parts[i];
    }

    bool dir_exists = false;
    const fs::path dir_path = resolve_asset_path(dir_rel, false, &dir_exists);
    auto st = std::make_shared<FindState>();

    std::error_code ec;
    if (dir_exists && fs::is_directory(dir_path, ec)) {
        for (const auto& entry : fs::directory_iterator(dir_path, ec)) {
            const std::string fname = entry.path().filename().string();
            if (!wildcard_match_ci(pat, fname)) continue;
            FindEntry fe;
            fe.name = fname;
            fe.is_dir = entry.is_directory(ec);
            fe.size = fe.is_dir ? 0u : entry.file_size(ec);
            fe.mtime_filetime = to_win_filetime(entry.last_write_time(ec));
            st->entries.push_back(std::move(fe));
        }
    }

    if (st->entries.empty()) {
        tls_last_error = kERROR_FILE_NOT_FOUND;
        ctx.eax = kINVALID_HANDLE_VALUE;
        ctx.ret_stdcall(mem, 8u);
        return;
    }

    write_find_data_a(mem, fd_va, st->entries[0]);
    st->index = 1u;

    HandleRecord rec;
    rec.kind = HandleKind::Find;
    rec.find = st;
    ctx.eax = insert_handle(std::move(rec));
    ctx.ret_stdcall(mem, 8u);
}

void k32_find_next_file_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h     = ctx.arg32(mem, 0);
    const uint32_t fd_va = ctx.arg32(mem, 1);
    HandleRecord rec;
    if (!get_handle(h, rec) || rec.kind != HandleKind::Find || !rec.find) {
        tls_last_error = kERROR_INVALID_HANDLE;
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    if (rec.find->index >= rec.find->entries.size()) {
        tls_last_error = kERROR_NO_MORE_FILES;
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    write_find_data_a(mem, fd_va, rec.find->entries[rec.find->index++]);
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 8u);
}

void k32_find_close(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h = ctx.arg32(mem, 0);
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    ctx.eax = (g_w32.handles.erase(h) > 0) ? 1u : 0u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_close_handle(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h = ctx.arg32(mem, 0);
    HandleRecord rec;
    {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        auto it = g_w32.handles.find(h);
        if (it == g_w32.handles.end()) {
            ctx.eax = 0u;
            ctx.ret_stdcall(mem, 4u);
            return;
        }
        rec = std::move(it->second);
        g_w32.handles.erase(it);
    }
    if (rec.kind == HandleKind::File && rec.file && rec.file->fp) {
        std::fclose(rec.file->fp);
        rec.file->fp = nullptr;
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_write_private_profile_string_a(CpuContext& ctx, GuestMemory& mem) {
    const std::string app  = mem.read_cstring(ctx.arg32(mem, 0));
    const std::string key  = mem.read_cstring(ctx.arg32(mem, 1));
    const uint32_t val_va  = ctx.arg32(mem, 2);
    const std::string file = mem.read_cstring(ctx.arg32(mem, 3));

    const fs::path p = resolve_asset_path(file, true);
    if (p.empty()) {
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 16u);
        return;
    }

    if (p.has_parent_path()) {
        std::error_code ec;
        fs::create_directories(p.parent_path(), ec);
    }

    std::vector<std::string> lines;
    {
        std::ifstream ifs(p);
        std::string line;
        while (std::getline(ifs, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            lines.push_back(line);
        }
    }

    const std::string sec_target = "[" + ascii_lower(app) + "]";
    const std::string key_low = ascii_lower(key);
    const bool delete_key = (val_va == 0u);
    const std::string val_str = delete_key ? std::string() : mem.read_cstring(val_va);

    int sec_start = -1;
    int sec_end   = static_cast<int>(lines.size());
    for (int i = 0; i < static_cast<int>(lines.size()); ++i) {
        const std::string low = ascii_lower(lines[i]);
        if (!low.empty() && low[0] == '[') {
            if (sec_start >= 0) {
                sec_end = i;
                break;
            }
            if (low == sec_target) {
                sec_start = i;
            }
        }
    }

    if (sec_start < 0) {
        if (!delete_key) {
            lines.push_back("[" + app + "]");
            lines.push_back(key + "= " + val_str);
        }
    } else {
        bool updated = false;
        for (int i = sec_start + 1; i < sec_end; ++i) {
            const size_t eq = lines[i].find('=');
            if (eq != std::string::npos) {
                std::string k = lines[i].substr(0, eq);
                while (!k.empty() && (k.back() == ' ' || k.back() == '\t')) k.pop_back();
                if (ascii_lower(k) == key_low) {
                    if (delete_key) {
                        lines.erase(lines.begin() + i);
                    } else {
                        lines[i] = key + "= " + val_str;
                    }
                    updated = true;
                    break;
                }
            }
        }
        if (!updated && !delete_key) {
            lines.insert(lines.begin() + sec_end, key + "= " + val_str);
        }
    }

    std::ofstream ofs(p, std::ios::trunc);
    if (!ofs.is_open()) {
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 16u);
        return;
    }
    for (const auto& l : lines) {
        ofs << l << "\r\n";
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 16u);
}

void k32_create_mutex_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t init_owner = ctx.arg32(mem, 1);
    const uint32_t name_va    = ctx.arg32(mem, 2);
    const std::string name    = name_va ? mem.read_cstring(name_va) : std::string();

    if (!name.empty()) {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        auto it = g_w32.named_mutexes.find(name);
        if (it != g_w32.named_mutexes.end()) {
            tls_last_error = kERROR_ALREADY_EXISTS;
            ctx.eax = it->second;
            ctx.ret_stdcall(mem, 12u);
            return;
        }
    }

    auto m = std::make_shared<SyncMutex>();
    if (init_owner != 0u) {
        m->owned = true;
        m->owner = std::this_thread::get_id();
        m->recursion = 1u;
    }
    HandleRecord rec;
    rec.kind = HandleKind::Mutex;
    rec.mutex = m;
    const uint32_t h = insert_handle(std::move(rec));
    if (!name.empty()) {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        g_w32.named_mutexes[name] = h;
    }
    tls_last_error = 0u;
    ctx.eax = h;
    ctx.ret_stdcall(mem, 12u);
}

void k32_release_mutex(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h = ctx.arg32(mem, 0);
    HandleRecord rec;
    if (!get_handle(h, rec) || rec.kind != HandleKind::Mutex || !rec.mutex) {
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 4u);
        return;
    }
    {
        std::lock_guard<std::mutex> lock(rec.mutex->mtx);
        if (rec.mutex->recursion > 0u) rec.mutex->recursion--;
        if (rec.mutex->recursion == 0u) {
            rec.mutex->owned = false;
            rec.mutex->cv.notify_one();
        }
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_create_event_a(CpuContext& ctx, GuestMemory& mem) {
    const bool manual_reset = ctx.arg32(mem, 1) != 0u;
    const bool init_state   = ctx.arg32(mem, 2) != 0u;

    auto ev = std::make_shared<SyncEvent>();
    ev->manual_reset = manual_reset;
    ev->signaled     = init_state;
    HandleRecord rec;
    rec.kind = HandleKind::Event;
    rec.event = ev;
    tls_last_error = 0u;
    ctx.eax = insert_handle(std::move(rec));
    ctx.ret_stdcall(mem, 16u);
}

void k32_set_event(CpuContext& ctx, GuestMemory& mem) {
    hle_win32_signal_event(ctx.arg32(mem, 0));
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_reset_event(CpuContext& ctx, GuestMemory& mem) {
    HandleRecord rec;
    if (get_handle(ctx.arg32(mem, 0), rec) && rec.kind == HandleKind::Event && rec.event) {
        std::lock_guard<std::mutex> lock(rec.event->mtx);
        rec.event->signaled = false;
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_create_semaphore_a(CpuContext& ctx, GuestMemory& mem) {
    const int32_t init_cnt = static_cast<int32_t>(ctx.arg32(mem, 1));
    const int32_t max_cnt  = static_cast<int32_t>(ctx.arg32(mem, 2));
    auto s = std::make_shared<SyncSemaphore>();
    s->count     = init_cnt;
    s->max_count = std::max<int32_t>(1, max_cnt);
    HandleRecord rec;
    rec.kind = HandleKind::Semaphore;
    rec.sem = s;
    ctx.eax = insert_handle(std::move(rec));
    ctx.ret_stdcall(mem, 16u);
}

void k32_release_semaphore(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h       = ctx.arg32(mem, 0);
    const int32_t  rel_cnt = static_cast<int32_t>(ctx.arg32(mem, 1));
    const uint32_t prev_va = ctx.arg32(mem, 2);

    HandleRecord rec;
    if (!get_handle(h, rec) || rec.kind != HandleKind::Semaphore || !rec.sem) {
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 12u);
        return;
    }
    std::lock_guard<std::mutex> lock(rec.sem->mtx);
    if (prev_va) mem.w32(prev_va, static_cast<uint32_t>(rec.sem->count));
    rec.sem->count = std::min(rec.sem->max_count, rec.sem->count + rel_cnt);
    rec.sem->cv.notify_all();
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 12u);
}

void k32_wait_single(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = wait_single_handle(ctx.arg32(mem, 0), ctx.arg32(mem, 1));
    ctx.ret_stdcall(mem, 8u);
}

void k32_wait_single_ex(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t h          = ctx.arg32(mem, 0);
    const uint32_t timeout_ms = ctx.arg32(mem, 1);
    const bool alertable      = ctx.arg32(mem, 2) != 0u;
    if (alertable && dispatch_pending_apcs(ctx, mem)) {
        ctx.eax = kWAIT_IO_COMPLETION;
        ctx.ret_stdcall(mem, 12u);
        return;
    }
    ctx.eax = wait_single_handle(h, timeout_ms);
    ctx.ret_stdcall(mem, 12u);
}

void k32_wait_multiple(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t count    = ctx.arg32(mem, 0);
    const uint32_t arr_va   = ctx.arg32(mem, 1);
    const bool wait_all     = ctx.arg32(mem, 2) != 0u;
    const uint32_t timeout  = ctx.arg32(mem, 3);

    if (count == 0u || count > 64u || arr_va == 0u) {
        ctx.eax = kWAIT_FAILED;
        ctx.ret_stdcall(mem, 16u);
        return;
    }

    const auto start = std::chrono::steady_clock::now();
    for (;;) {
        if (g_w32.quit_requested.load(std::memory_order_acquire)) {
            if (tls_is_worker) throw GuestThreadExit{0u};
            ctx.eax = kWAIT_OBJECT_0;
            ctx.ret_stdcall(mem, 16u);
            return;
        }
        bool all_ok = true;
        bool any_valid = false;
        for (uint32_t i = 0; i < count; ++i) {
            const uint32_t res = wait_single_handle(mem.r32(arr_va + i * 4u), 0u);
            if (res == kWAIT_OBJECT_0 && !wait_all) {
                ctx.eax = kWAIT_OBJECT_0 + i;
                ctx.ret_stdcall(mem, 16u);
                return;
            }
            if (res != kWAIT_FAILED) any_valid = true;
            if (res != kWAIT_OBJECT_0) all_ok = false;
        }
        if (!any_valid) {
            ctx.eax = kWAIT_FAILED;
            ctx.ret_stdcall(mem, 16u);
            return;
        }
        if (wait_all && all_ok) {
            ctx.eax = kWAIT_OBJECT_0;
            ctx.ret_stdcall(mem, 16u);
            return;
        }
        if (timeout == 0u) {
            ctx.eax = kWAIT_TIMEOUT;
            ctx.ret_stdcall(mem, 16u);
            return;
        }
        if (timeout != 0xFFFFFFFFu) {
            const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - start).count();
            if (elapsed >= static_cast<int64_t>(timeout)) {
                ctx.eax = kWAIT_TIMEOUT;
                ctx.ret_stdcall(mem, 16u);
                return;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

std::shared_ptr<std::recursive_mutex> get_crit_sec(uint32_t cs_va) {
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    auto& m = g_w32.crit_sections[cs_va];
    if (!m) m = std::make_shared<std::recursive_mutex>();
    return m;
}

void k32_init_crit_sec(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t cs_va = ctx.arg32(mem, 0);
    get_crit_sec(cs_va);
    ctx.ret_stdcall(mem, 4u);
}

void k32_delete_crit_sec(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t cs_va = ctx.arg32(mem, 0);
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    g_w32.crit_sections.erase(cs_va);
    ctx.ret_stdcall(mem, 4u);
}

void k32_enter_crit_sec(CpuContext& ctx, GuestMemory& mem) {
    get_crit_sec(ctx.arg32(mem, 0))->lock();
    ctx.ret_stdcall(mem, 4u);
}

void k32_leave_crit_sec(CpuContext& ctx, GuestMemory& mem) {
    get_crit_sec(ctx.arg32(mem, 0))->unlock();
    ctx.ret_stdcall(mem, 4u);
}

void k32_create_thread(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t start_va = ctx.arg32(mem, 2);
    const uint32_t param_va = ctx.arg32(mem, 3);
    const uint32_t tid_va   = ctx.arg32(mem, 5);

    if (g_w32.quit_requested.load(std::memory_order_acquire)) {
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 24u);
        return;
    }

    const uint32_t spawn_no = g_log.thread_spawn_count.fetch_add(1u, std::memory_order_relaxed) + 1u;
    if (start_va == 0u) {
        const uint32_t fails = g_log.thread_fail_count.fetch_add(1u, std::memory_order_relaxed) + 1u;
        hle_win32_log("CreateThread FAILED #%u (spawn #%u): null start_va", fails, spawn_no);
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 24u);
        return;
    }

    const uint32_t child_esp = mem.alloc_thread_stack();
    if (child_esp == 0u) {
        const uint32_t fails = g_log.thread_fail_count.fetch_add(1u, std::memory_order_relaxed) + 1u;
        hle_win32_log("CreateThread FAILED #%u (spawn #%u): start=0x%08x esp=0x%08x",
                      fails, spawn_no, start_va, child_esp);
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 24u);
        return;
    }

    auto th = std::make_shared<SyncThread>();
    th->tid = g_w32.next_tid.fetch_add(1u, std::memory_order_relaxed);
    th->done_event->manual_reset = true;
    if (tid_va) mem.w32(tid_va, th->tid);

    const uint32_t child_tid = th->tid;
    GuestMemory* mem_ptr = &mem;

    {
        std::lock_guard<std::mutex> wlk(g_w32.worker_mtx);
        ++g_w32.active_workers;
    }

    try {
        std::thread([mem_ptr, start_va, param_va, child_esp, child_tid, th]() {
            tls_tid = child_tid;
            tls_is_worker = true;
            tls_pending_apcs.clear();
#if defined(__APPLE__)
            void* pool = objc_autoreleasePoolPush();
#endif
            struct WorkerCleanupGuard {
                GuestMemory* m;
                uint32_t esp;
                uint32_t tid;
                std::shared_ptr<SyncThread> thread_obj;
                uint32_t exit_code = 0u;
#if defined(__APPLE__)
                void* autorelease_pool;
#endif
                ~WorkerCleanupGuard() {
                    tls_pending_apcs.clear();
                    m->free_thread_stack(esp);
                    {
                        std::lock_guard<std::mutex> slk(g_w32.state_mtx);
                        g_w32.thread_queues.erase(tid);
                    }
                    thread_obj->exit_code.store(exit_code, std::memory_order_relaxed);
                    {
                        std::lock_guard<std::mutex> dlk(thread_obj->done_event->mtx);
                        thread_obj->done_event->signaled = true;
                        thread_obj->done_event->cv.notify_all();
                    }
#if defined(__APPLE__)
                    if (autorelease_pool != nullptr) {
                        objc_autoreleasePoolPop(autorelease_pool);
                    }
#endif
                    {
                        std::lock_guard<std::mutex> wlk(g_w32.worker_mtx);
                        if (g_w32.active_workers > 0) --g_w32.active_workers;
                        g_w32.worker_cv.notify_all();
                    }
                }
            } cleanup{
                mem_ptr, child_esp, child_tid, th, 0u
#if defined(__APPLE__)
                , pool
#endif
            };

            try {
                CpuContext tctx;
                tctx.reset(child_esp, GuestMemory::kTebBase);
                tctx.push32(*mem_ptr, param_va);
                tctx.push32(*mem_ptr, 0x00FFFFF3u); // Sentinel return EIP
                call_indirect(tctx, *mem_ptr, start_va);
                cleanup.exit_code = tctx.eax;
            } catch (const GuestThreadExit& e) {
                cleanup.exit_code = e.code;
            }
        }).detach();
    } catch (...) {
        mem.free_thread_stack(child_esp);
        {
            std::lock_guard<std::mutex> wlk(g_w32.worker_mtx);
            if (g_w32.active_workers > 0) --g_w32.active_workers;
            g_w32.worker_cv.notify_all();
        }
        const uint32_t fails = g_log.thread_fail_count.fetch_add(1u, std::memory_order_relaxed) + 1u;
        hle_win32_log("CreateThread FAILED #%u (spawn #%u): std::thread launch error", fails, spawn_no);
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 24u);
        return;
    }

    HandleRecord rec;
    rec.kind = HandleKind::Thread;
    rec.thread = th;
    ctx.eax = insert_handle(std::move(rec));
    ctx.ret_stdcall(mem, 24u);
}

void k32_exit_thread(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t exit_code = ctx.arg32(mem, 0);
    if (tls_is_worker) {
        throw GuestThreadExit{exit_code};
    }
    ctx.ret_stdcall(mem, 4u);
}

void k32_sleep(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ms = ctx.arg32(mem, 0);
    if (g_w32.quit_requested.load(std::memory_order_acquire)) {
        if (tls_is_worker) throw GuestThreadExit{0u};
        ctx.ret_stdcall(mem, 4u);
        return;
    }
    if (ms > 0u) {
        std::this_thread::sleep_for(std::chrono::milliseconds(std::min(ms, 50u)));
    } else {
        std::this_thread::yield();
    }
    ctx.ret_stdcall(mem, 4u);
}

void k32_sleep_ex(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ms      = ctx.arg32(mem, 0);
    const bool alertable   = ctx.arg32(mem, 1) != 0u;

    if (alertable && dispatch_pending_apcs(ctx, mem)) {
        ctx.eax = kWAIT_IO_COMPLETION;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    if (g_w32.quit_requested.load(std::memory_order_acquire)) {
        if (tls_is_worker) throw GuestThreadExit{0u};
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 8u);
        return;
    }
    if (ms > 0u) {
        std::this_thread::sleep_for(std::chrono::milliseconds(std::min(ms, 50u)));
        if (alertable && dispatch_pending_apcs(ctx, mem)) {
            ctx.eax = kWAIT_IO_COMPLETION;
            ctx.ret_stdcall(mem, 8u);
            return;
        }
    } else {
        std::this_thread::yield();
    }
    ctx.eax = 0u;
    ctx.ret_stdcall(mem, 8u);
}

void k32_get_tick_count(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = tick_ms();
    ctx.ret_stdcall(mem, 0u);
}

void k32_query_performance_counter(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 0);
    const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now() - g_w32.boot_time).count();
    if (out_va) mem.w64(out_va, static_cast<uint64_t>(ns));
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_query_performance_frequency(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t out_va = ctx.arg32(mem, 0);
    if (out_va) mem.w64(out_va, 1000000000ULL);
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_get_local_time(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t st_va = ctx.arg32(mem, 0);
    if (st_va != 0u) {
        const std::time_t t = std::time(nullptr);
        std::tm tm_val{};
#if !defined(_WIN32)
        ::localtime_r(&t, &tm_val);
#else
        ::localtime_s(&tm_val, &t);
#endif
        mem.w16(st_va + 0u, static_cast<uint16_t>(tm_val.tm_year + 1900));
        mem.w16(st_va + 2u, static_cast<uint16_t>(tm_val.tm_mon + 1));
        mem.w16(st_va + 4u, static_cast<uint16_t>(tm_val.tm_wday));
        mem.w16(st_va + 6u, static_cast<uint16_t>(tm_val.tm_mday));
        mem.w16(st_va + 8u, static_cast<uint16_t>(tm_val.tm_hour));
        mem.w16(st_va + 10u, static_cast<uint16_t>(tm_val.tm_min));
        mem.w16(st_va + 12u, static_cast<uint16_t>(tm_val.tm_sec));
        mem.w16(st_va + 14u, 0u);
    }
    ctx.ret_stdcall(mem, 4u);
}

void k32_get_disk_free_space_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t spc = ctx.arg32(mem, 1);
    const uint32_t bps = ctx.arg32(mem, 2);
    const uint32_t nfc = ctx.arg32(mem, 3);
    const uint32_t tnc = ctx.arg32(mem, 4);
    if (spc) mem.w32(spc, 8u);
    if (bps) mem.w32(bps, 512u);
    if (nfc) mem.w32(nfc, 262144u); // ~1 GB free
    if (tnc) mem.w32(tnc, 524288u);
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 20u);
}

void k32_global_alloc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t flags = ctx.arg32(mem, 0);
    const uint32_t bytes = ctx.arg32(mem, 1);
    const uint32_t va = (flags & 0x0040u) ? mem.guest_calloc(1u, bytes) : mem.guest_alloc(bytes);
    ctx.eax = va;
    ctx.ret_stdcall(mem, 8u);
}

void k32_global_lock(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = ctx.arg32(mem, 0);
    ctx.ret_stdcall(mem, 4u);
}

void k32_global_unlock(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_virtual_alloc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t size = ctx.arg32(mem, 1);
    ctx.eax = mem.guest_calloc(1u, std::max<uint32_t>(size, 4096u));
    ctx.ret_stdcall(mem, 16u);
}

void k32_virtual_free(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t addr = ctx.arg32(mem, 0);
    const uint32_t type = ctx.arg32(mem, 2);
    if (type & 0x8000u) mem.guest_free(addr);
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 12u);
}

void k32_heap_alloc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t flags = ctx.arg32(mem, 1);
    const uint32_t bytes = ctx.arg32(mem, 2);
    ctx.eax = (flags & 8u) ? mem.guest_calloc(1u, bytes) : mem.guest_alloc(bytes);
    ctx.ret_stdcall(mem, 12u);
}

void k32_heap_realloc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ptr_va = ctx.arg32(mem, 2);
    const uint32_t bytes  = ctx.arg32(mem, 3);
    ctx.eax = mem.guest_realloc(ptr_va, bytes);
    ctx.ret_stdcall(mem, 16u);
}

void k32_heap_free(CpuContext& ctx, GuestMemory& mem) {
    mem.guest_free(ctx.arg32(mem, 2));
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 12u);
}

void k32_heap_size(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = mem.guest_msize(ctx.arg32(mem, 2));
    ctx.ret_stdcall(mem, 12u);
}

void k32_multibyte_to_widechar(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t cp      = ctx.arg32(mem, 0);
    const uint32_t src_va  = ctx.arg32(mem, 2);
    const int32_t  src_len = static_cast<int32_t>(ctx.arg32(mem, 3));
    const uint32_t dst_va  = ctx.arg32(mem, 4);
    const int32_t  dst_cap = static_cast<int32_t>(ctx.arg32(mem, 5));

    const char* src_ptr = reinterpret_cast<const char*>(mem.ptr(src_va));
    const auto wchars = decode_to_utf16(cp, src_ptr, src_len);
    if (dst_cap == 0) {
        ctx.eax = static_cast<uint32_t>(wchars.size());
        ctx.ret_stdcall(mem, 24u);
        return;
    }
    const size_t n = std::min(wchars.size(), static_cast<size_t>(std::max(0, dst_cap)));
    for (size_t i = 0; i < n; ++i) {
        mem.w16(dst_va + static_cast<uint32_t>(i * 2u), wchars[i]);
    }
    ctx.eax = static_cast<uint32_t>(n);
    ctx.ret_stdcall(mem, 24u);
}

void k32_widechar_to_multibyte(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t cp      = ctx.arg32(mem, 0);
    const uint32_t src_va  = ctx.arg32(mem, 2);
    const int32_t  src_len = static_cast<int32_t>(ctx.arg32(mem, 3));
    const uint32_t dst_va  = ctx.arg32(mem, 4);
    const int32_t  dst_cap = static_cast<int32_t>(ctx.arg32(mem, 5));

    const uint16_t* src_ptr = reinterpret_cast<const uint16_t*>(mem.ptr(src_va));
    const auto bytes = encode_from_utf16(cp, src_ptr, src_len);
    if (dst_cap == 0) {
        ctx.eax = static_cast<uint32_t>(bytes.size());
        ctx.ret_stdcall(mem, 32u);
        return;
    }
    const size_t n = std::min(bytes.size(), static_cast<size_t>(std::max(0, dst_cap)));
    mem.write_bytes(dst_va, bytes.data(), n);
    ctx.eax = static_cast<uint32_t>(n);
    ctx.ret_stdcall(mem, 32u);
}

void k32_load_library_a(CpuContext& ctx, GuestMemory& mem) {
    const std::string dll = ascii_lower(mem.read_cstring(ctx.arg32(mem, 0)));
    // Zero DRM bypass: unshimmed external DLLs (including reg.dll) MUST cleanly return NULL.
    if (dll == "kernel32.dll" || dll == "kernel32") { ctx.eax = 0x70010000u; }
    else if (dll == "user32.dll" || dll == "user32") { ctx.eax = 0x70020000u; }
    else if (dll == "d3d9.dll" || dll == "d3d9") { ctx.eax = 0x70030000u; }
    else if (dll == "dinput8.dll" || dll == "dinput8") { ctx.eax = 0x70040000u; }
    else if (dll == "dsound.dll" || dll == "dsound") { ctx.eax = 0x70050000u; }
    else if (dll == "ws2_32.dll" || dll == "ws2_32") { ctx.eax = 0x70060000u; }
    else {
        tls_last_error = kERROR_FILE_NOT_FOUND;
        ctx.eax = 0u;
    }
    ctx.ret_stdcall(mem, 4u);
}

void k32_get_module_handle_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t name_va = ctx.arg32(mem, 0);
    if (name_va == 0u) {
        ctx.eax = kHINST_MAIN;
        ctx.ret_stdcall(mem, 4u);
        return;
    }
    const std::string mod = ascii_lower(mem.read_cstring(name_va));
    if (mod == "mbaa.exe") ctx.eax = kHINST_MAIN;
    else if (mod == "kernel32.dll" || mod == "kernel32") ctx.eax = 0x70010000u;
    else if (mod == "user32.dll" || mod == "user32") ctx.eax = 0x70020000u;
    else ctx.eax = 0u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_get_module_filename_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t buf_va = ctx.arg32(mem, 1);
    const uint32_t cap    = ctx.arg32(mem, 2);
    const std::string p = g_w32.assets_dir.empty() ? "C:\\MBAACC\\MBAA.exe" : (g_w32.assets_dir + "/MBAA.exe");
    ctx.eax = mem.write_cstring(buf_va, p, cap);
    ctx.ret_stdcall(mem, 12u);
}

void k32_get_computer_name_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t buf_va = ctx.arg32(mem, 0);
    const uint32_t pcb_va = ctx.arg32(mem, 1);
    const uint32_t cap = pcb_va ? mem.r32(pcb_va) : 0u;
    const std::string name = "IPHONE-SE-2020";
    const uint32_t written = mem.write_cstring(buf_va, name, cap);
    if (pcb_va) mem.w32(pcb_va, written);
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 8u);
}

void k32_get_command_line_a(CpuContext& ctx, GuestMemory& mem) {
    if (g_w32.cmdline_va == 0u) {
        g_w32.cmdline_va = mem.alloc_thunk_block(64u, 4u);
        mem.write_cstring(g_w32.cmdline_va, "MBAA.exe", 64u);
    }
    ctx.eax = g_w32.cmdline_va;
    ctx.ret_stdcall(mem, 0u);
}

void k32_get_env_strings_a(CpuContext& ctx, GuestMemory& mem) {
    if (g_w32.env_ansi_va == 0u) {
        g_w32.env_ansi_va = mem.alloc_thunk_block(64u, 4u);
        mem.write_cstring(g_w32.env_ansi_va, "PATH=.", 64u);
    }
    ctx.eax = g_w32.env_ansi_va;
    ctx.ret_stdcall(mem, 0u);
}

void k32_get_env_strings_w(CpuContext& ctx, GuestMemory& mem) {
    if (g_w32.env_wide_va == 0u) {
        g_w32.env_wide_va = mem.alloc_thunk_block(64u, 4u);
    }
    ctx.eax = g_w32.env_wide_va;
    ctx.ret_stdcall(mem, 0u);
}

void k32_interlocked_inc(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t va = ctx.arg32(mem, 0);
    std::lock_guard<std::mutex> lock(g_w32.interlocked_mtx);
    const int32_t v = static_cast<int32_t>(mem.r32(va)) + 1;
    mem.w32(va, static_cast<uint32_t>(v));
    ctx.eax = static_cast<uint32_t>(v);
    ctx.ret_stdcall(mem, 4u);
}

void k32_interlocked_dec(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t va = ctx.arg32(mem, 0);
    std::lock_guard<std::mutex> lock(g_w32.interlocked_mtx);
    const int32_t v = static_cast<int32_t>(mem.r32(va)) - 1;
    mem.w32(va, static_cast<uint32_t>(v));
    ctx.eax = static_cast<uint32_t>(v);
    ctx.ret_stdcall(mem, 4u);
}

void k32_tls_alloc(CpuContext& ctx, GuestMemory& mem) {
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    for (uint32_t i = 0; i < 64u; ++i) {
        if (!g_w32.tls_used[i]) {
            g_w32.tls_used[i] = true;
            ctx.eax = i;
            ctx.ret_stdcall(mem, 0u);
            return;
        }
    }
    ctx.eax = 0xFFFFFFFFu;
    ctx.ret_stdcall(mem, 0u);
}

void k32_tls_free(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t idx = ctx.arg32(mem, 0);
    if (idx < 64u) {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        g_w32.tls_used[idx] = false;
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_tls_get_value(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t idx = ctx.arg32(mem, 0);
    ctx.eax = (idx < 64u) ? tls_values[idx] : 0u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_tls_set_value(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t idx = ctx.arg32(mem, 0);
    const uint32_t val = ctx.arg32(mem, 1);
    if (idx < 64u) tls_values[idx] = val;
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 8u);
}

void k32_get_version_ex_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t info_va = ctx.arg32(mem, 0);
    if (info_va == 0u) {
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 4u);
        return;
    }
    const uint32_t cb = mem.r32(info_va);
    if (cb >= 148u) {
        mem.zero_bytes(info_va + 4u, cb - 4u);
        mem.w32(info_va + 4u, 6u);    // dwMajorVersion (Windows 7)
        mem.w32(info_va + 8u, 1u);    // dwMinorVersion
        mem.w32(info_va + 12u, 7601u);// dwBuildNumber
        mem.w32(info_va + 16u, 2u);   // VER_PLATFORM_WIN32_NT
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void k32_get_system_time_as_file_time(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t ft_va = ctx.arg32(mem, 0);
    if (ft_va != 0u) {
        const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        // FILETIME epoch 1601-01-01 -> Unix epoch 1970-01-01 offset in 100ns ticks
        const uint64_t ft = static_cast<uint64_t>(ns / 100) + 116444736000000000ULL;
        mem.w64(ft_va, ft);
    }
    ctx.ret_stdcall(mem, 4u);
}

void k32_compare_string_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t flags = ctx.arg32(mem, 1);
    const uint32_t s1_va = ctx.arg32(mem, 2);
    const int32_t  c1    = static_cast<int32_t>(ctx.arg32(mem, 3));
    const uint32_t s2_va = ctx.arg32(mem, 4);
    const int32_t  c2    = static_cast<int32_t>(ctx.arg32(mem, 5));

    const bool nocase = (flags & 1u) != 0u;
    std::string a = (c1 < 0) ? mem.read_cstring(s1_va)
                             : std::string(reinterpret_cast<const char*>(mem.ptr(s1_va)), static_cast<size_t>(c1));
    std::string b = (c2 < 0) ? mem.read_cstring(s2_va)
                             : std::string(reinterpret_cast<const char*>(mem.ptr(s2_va)), static_cast<size_t>(c2));
    if (nocase) {
        a = ascii_lower(a);
        b = ascii_lower(b);
    }
    ctx.eax = (a < b) ? 1u : (a > b ? 3u : 2u); // CSTR_LESS_THAN / GREATER_THAN / EQUAL
    ctx.ret_stdcall(mem, 24u);
}

void k32_compare_string_w(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t flags = ctx.arg32(mem, 1);
    const uint32_t s1_va = ctx.arg32(mem, 2);
    const int32_t  c1    = static_cast<int32_t>(ctx.arg32(mem, 3));
    const uint32_t s2_va = ctx.arg32(mem, 4);
    const int32_t  c2    = static_cast<int32_t>(ctx.arg32(mem, 5));

    const bool nocase = (flags & 1u) != 0u;
    auto read_w = [&](uint32_t va, int32_t len) {
        std::u16string out;
        if (!va) return out;
        if (len < 0) {
            for (uint32_t i = 0; i < 4096u; ++i) {
                const uint16_t ch = mem.r16(va + i * 2u);
                if (ch == 0u) break;
                out.push_back(static_cast<char16_t>(
                    (nocase && ch >= u'A' && ch <= u'Z') ? (ch + 32u) : ch));
            }
        } else {
            for (int32_t i = 0; i < len; ++i) {
                const uint16_t ch = mem.r16(va + static_cast<uint32_t>(i * 2));
                out.push_back(static_cast<char16_t>(
                    (nocase && ch >= u'A' && ch <= u'Z') ? (ch + 32u) : ch));
            }
        }
        return out;
    };
    const std::u16string a = read_w(s1_va, c1);
    const std::u16string b = read_w(s2_va, c2);
    ctx.eax = (a < b) ? 1u : (a > b ? 3u : 2u);
    ctx.ret_stdcall(mem, 24u);
}

// ---------------------------------------------------------------------------
// USER32 Shims
// ---------------------------------------------------------------------------
void u32_peek_message_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t msg_va   = ctx.arg32(mem, 0);
    const uint32_t remove   = ctx.arg32(mem, 4);
    const uint32_t tid      = current_tid();
    auto q = get_thread_queue(tid);

    {
        std::lock_guard<std::mutex> lock(q->mtx);
        if (!q->msgs.empty()) {
            const ThreadMessage m = q->msgs.front();
            if (remove & 1u) q->msgs.pop_front();
            if (msg_va) {
                mem.w32(msg_va + 0u, m.hwnd);
                mem.w32(msg_va + 4u, m.message);
                mem.w32(msg_va + 8u, m.wparam);
                mem.w32(msg_va + 12u, m.lparam);
                mem.w32(msg_va + 16u, m.time_ms);
                mem.w32(msg_va + 20u, 0u);
                mem.w32(msg_va + 24u, 0u);
            }
            ctx.eax = 1u;
            ctx.ret_stdcall(mem, 20u);
            return;
        }
    }

    // Cooperative yield to MTKView 60 Hz frame step on the main thread
    if (std::this_thread::get_id() == g_w32.main_thread_id && g_w32.frame_yield_cb) {
        const bool keep_running = g_w32.frame_yield_cb();
        if (!keep_running || g_w32.quit_requested.load(std::memory_order_acquire)) {
            if (msg_va) {
                mem.zero_bytes(msg_va, 28u);
                mem.w32(msg_va + 4u, kWM_QUIT);
                mem.w32(msg_va + 8u, static_cast<uint32_t>(g_w32.quit_code.load(std::memory_order_relaxed)));
            }
            ctx.eax = 1u;
            ctx.ret_stdcall(mem, 20u);
            return;
        }
    }

    ctx.eax = 0u;
    ctx.ret_stdcall(mem, 20u);
}

void u32_post_thread_message_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t tid = ctx.arg32(mem, 0);
    ThreadMessage m;
    m.message = ctx.arg32(mem, 1);
    m.wparam  = ctx.arg32(mem, 2);
    m.lparam  = ctx.arg32(mem, 3);
    m.time_ms = tick_ms();
    auto q = get_thread_queue(tid);
    {
        std::lock_guard<std::mutex> lock(q->mtx);
        q->msgs.push_back(m);
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 16u);
}

void u32_post_quit_message(CpuContext& ctx, GuestMemory& mem) {
    const int code = static_cast<int>(ctx.arg32(mem, 0));
    hle_win32_log("PostQuitMessage(%d)", code);
    hle_win32_post_quit(code);
    ctx.ret_stdcall(mem, 4u);
}

void u32_message_box_a(CpuContext& ctx, GuestMemory& mem) {
    const std::string text  = mem.read_cstring(ctx.arg32(mem, 1));
    const std::string title = mem.read_cstring(ctx.arg32(mem, 2));
    hle_win32_log("MessageBoxA [%s]: %s", title.c_str(), text.c_str());
    ctx.eax = kIDOK;
    ctx.ret_stdcall(mem, 16u);
}

void u32_destroy_window(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t hwnd = ctx.arg32(mem, 0);
    const uint32_t cnt = g_log.destroy_window_calls.fetch_add(1u, std::memory_order_relaxed) + 1u;
    if (cnt <= 3u) {
        hle_win32_log("DestroyWindow(0x%08x) call #%u", hwnd, cnt);
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 4u);
}

void u32_dialog_box_param_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t dlg_id = ctx.arg32(mem, 1);
    const uint32_t proc_va = ctx.arg32(mem, 3);
    const uint32_t cnt = g_log.dialog_box_calls.fetch_add(1u, std::memory_order_relaxed) + 1u;
    if (cnt <= 3u) {
        hle_win32_log("DialogBoxParamA(res=%u, proc=0x%08x) call #%u -> IDOK", dlg_id, proc_va, cnt);
    }
    ctx.eax = kIDOK;
    ctx.ret_stdcall(mem, 20u);
}

void u32_show_cursor(CpuContext& ctx, GuestMemory& mem) {
    const bool show = ctx.arg32(mem, 0) != 0u;
    const int32_t next = show
        ? (g_log.cursor_display_count.fetch_add(1, std::memory_order_relaxed) + 1)
        : (g_log.cursor_display_count.fetch_sub(1, std::memory_order_relaxed) - 1);
    ctx.eax = static_cast<uint32_t>(next);
    ctx.ret_stdcall(mem, 4u);
}

void u32_get_client_rect(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t rect_va = ctx.arg32(mem, 1);
    if (rect_va) {
        mem.w32(rect_va + 0u, 0u);
        mem.w32(rect_va + 4u, 0u);
        mem.w32(rect_va + 8u, g_w32.screen_w);
        mem.w32(rect_va + 12u, g_w32.screen_h);
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 8u);
}

void u32_adjust_window_rect(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 12u);
}

void u32_get_system_metrics(CpuContext& ctx, GuestMemory& mem) {
    const int idx = static_cast<int>(ctx.arg32(mem, 0));
    uint32_t val = 0u;
    if (idx == 0) val = g_w32.screen_w;      // SM_CXSCREEN
    else if (idx == 1) val = g_w32.screen_h; // SM_CYSCREEN
    else if (idx == 4) val = 24u;            // SM_CYCAPTION
    else if (idx == 7 || idx == 32) val = 4u;
    else if (idx == 8 || idx == 33) val = 4u;
    ctx.eax = val;
    ctx.ret_stdcall(mem, 4u);
}

void u32_get_key_state(CpuContext& ctx, GuestMemory& mem) {
    const int vk = static_cast<int>(ctx.arg32(mem, 0));
    ctx.eax = static_cast<uint16_t>(input_get_vk_state(vk));
    ctx.ret_stdcall(mem, 4u);
}

void u32_wsprintf_a_cdecl(CpuContext& ctx, GuestMemory& mem) {
    // __cdecl varargs: args at [esp+4] = dst_va, [esp+8] = fmt_va, [esp+12...] = args
    const uint32_t dst_va = ctx.arg32(mem, 0);
    const std::string fmt = mem.read_cstring(ctx.arg32(mem, 1));
    std::string out;
    uint32_t arg_idx = 2u;

    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] != '%' || i + 1 >= fmt.size()) {
            out.push_back(fmt[i]);
            continue;
        }
        size_t j = i + 1;
        std::string spec = "%";
        while (j < fmt.size() && (fmt[j] == '-' || fmt[j] == '+' || fmt[j] == '0' ||
                                  fmt[j] == ' ' || std::isdigit(static_cast<unsigned char>(fmt[j])) ||
                                  fmt[j] == '.')) {
            spec.push_back(fmt[j++]);
        }
        if (j >= fmt.size()) break;
        const char conv = fmt[j];
        spec.push_back(conv);
        i = j;

        if (conv == '%') {
            out.push_back('%');
            continue;
        }
        const uint32_t v = ctx.arg32(mem, arg_idx++);
        char buf[256] = {};
        if (conv == 's') {
            out += mem.read_cstring(v);
        } else if (conv == 'd' || conv == 'i') {
            std::snprintf(buf, sizeof(buf), spec.c_str(), static_cast<int32_t>(v));
            out += buf;
        } else if (conv == 'u' || conv == 'x' || conv == 'X') {
            std::snprintf(buf, sizeof(buf), spec.c_str(), v);
            out += buf;
        } else if (conv == 'c') {
            out.push_back(static_cast<char>(v & 0xFFu));
        } else {
            out += spec;
        }
    }

    ctx.eax = mem.write_cstring(dst_va, out, 4096u);
    ctx.ret_cdecl(mem);
}

void u32_set_rect(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t r = ctx.arg32(mem, 0);
    if (r) {
        mem.w32(r + 0u, ctx.arg32(mem, 1));
        mem.w32(r + 4u, ctx.arg32(mem, 2));
        mem.w32(r + 8u, ctx.arg32(mem, 3));
        mem.w32(r + 12u, ctx.arg32(mem, 4));
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 20u);
}

// ---------------------------------------------------------------------------
// GDI32 Shims (CoreText Shift-JIS glyph rasterizer)
// ---------------------------------------------------------------------------
void gdi_create_font_indirect_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t lf_va = ctx.arg32(mem, 0);
    auto font = std::make_shared<FontState>();
    if (lf_va) {
        font->height = std::abs(static_cast<int32_t>(mem.r32(lf_va + 0u)));
        if (font->height == 0) font->height = 16;
        font->weight = static_cast<int32_t>(mem.r32(lf_va + 16u));
        std::string face = mem.read_cstring(lf_va + 28u, 32u);
        if (!face.empty()) font->face = face;
    }
    HandleRecord rec;
    rec.kind = HandleKind::Font;
    rec.font = font;
    ctx.eax = insert_handle(std::move(rec));
    ctx.ret_stdcall(mem, 4u);
}

void gdi_select_object(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t hdc  = ctx.arg32(mem, 0);
    const uint32_t hobj = ctx.arg32(mem, 1);
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    const uint32_t prev = g_w32.selected_font_by_dc[hdc];
    g_w32.selected_font_by_dc[hdc] = hobj;
    ctx.eax = prev ? prev : 0x10000010u;
    ctx.ret_stdcall(mem, 8u);
}

void gdi_get_text_metrics_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t hdc   = ctx.arg32(mem, 0);
    const uint32_t tm_va = ctx.arg32(mem, 1);
    int32_t height = 16;
    {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        const uint32_t hf = g_w32.selected_font_by_dc[hdc];
        auto it = g_w32.handles.find(hf);
        if (it != g_w32.handles.end() && it->second.font) {
            height = it->second.font->height;
        }
    }
    if (tm_va) {
        mem.zero_bytes(tm_va, 56u);
        mem.w32(tm_va + 0u, static_cast<uint32_t>(height));
        mem.w32(tm_va + 4u, static_cast<uint32_t>((height * 4) / 5)); // tmAscent
        mem.w32(tm_va + 8u, static_cast<uint32_t>(height - (height * 4) / 5)); // tmDescent
        mem.w32(tm_va + 20u, static_cast<uint32_t>(height / 2)); // tmAveCharWidth
        mem.w32(tm_va + 24u, static_cast<uint32_t>(height));     // tmMaxCharWidth
    }
    ctx.eax = 1u;
    ctx.ret_stdcall(mem, 8u);
}

void gdi_get_glyph_outline_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t hdc    = ctx.arg32(mem, 0);
    const uint32_t u_char = ctx.arg32(mem, 1);
    const uint32_t format = ctx.arg32(mem, 2); // 1=GGO_BITMAP, 6=GGO_GRAY8_BITMAP
    const uint32_t gm_va  = ctx.arg32(mem, 3);
    const uint32_t cb_buf = ctx.arg32(mem, 4);
    const uint32_t buf_va = ctx.arg32(mem, 5);

    int32_t font_px = 16;
    {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        const uint32_t hf = g_w32.selected_font_by_dc[hdc];
        auto it = g_w32.handles.find(hf);
        if (it != g_w32.handles.end() && it->second.font) {
            font_px = std::clamp(it->second.font->height, 8, 96);
        }
    }

    uint32_t bw = 1, bh = 1;
    int32_t origin_x = 0, origin_y = font_px - 2;
    int16_t adv_x = static_cast<int16_t>((u_char > 0xFFu) ? font_px : (font_px / 2));
    std::vector<uint8_t> gray;

#if defined(__APPLE__)
    uint8_t sjis[3] = {};
    CFIndex sjis_len = 0;
    if (u_char > 0xFFu) {
        sjis[0] = static_cast<uint8_t>((u_char >> 8) & 0xFFu);
        sjis[1] = static_cast<uint8_t>(u_char & 0xFFu);
        sjis_len = 2;
    } else {
        sjis[0] = static_cast<uint8_t>(u_char & 0xFFu);
        sjis_len = 1;
    }

    UniChar uni = static_cast<UniChar>(u_char & 0x7Fu);
    CFStringRef cf = CFStringCreateWithBytes(kCFAllocatorDefault, sjis, sjis_len, kCFStringEncodingDOSJapanese, false);
    if (cf && CFStringGetLength(cf) > 0) {
        uni = CFStringGetCharacterAtIndex(cf, 0);
    }
    if (cf) CFRelease(cf);

    CTFontRef font = CTFontCreateWithName(CFSTR("HiraginoSans-W3"), static_cast<CGFloat>(font_px), nullptr);
    if (!font) font = CTFontCreateUIFontForLanguage(kCTFontUIFontSystem, static_cast<CGFloat>(font_px), CFSTR("ja"));

    if (font) {
        CGGlyph glyph = 0;
        if (CTFontGetGlyphsForCharacters(font, &uni, &glyph, 1)) {
            CGSize adv{};
            CTFontGetAdvancesForGlyphs(font, kCTFontOrientationHorizontal, &glyph, &adv, 1);
            adv_x = static_cast<int16_t>(std::lround(adv.width));

            CGRect bbox = CTFontGetBoundingRectsForGlyphs(font, kCTFontOrientationHorizontal, &glyph, nullptr, 1);
            if (bbox.size.width > 0.0 && bbox.size.height > 0.0) {
                const int x0 = static_cast<int>(std::floor(bbox.origin.x));
                const int y0 = static_cast<int>(std::floor(bbox.origin.y));
                const int x1 = static_cast<int>(std::ceil(bbox.origin.x + bbox.size.width));
                const int y1 = static_cast<int>(std::ceil(bbox.origin.y + bbox.size.height));
                bw = static_cast<uint32_t>(std::max(1, x1 - x0));
                bh = static_cast<uint32_t>(std::max(1, y1 - y0));
                origin_x = x0;
                origin_y = y1;

                gray.assign(bw * bh, 0u);
                CGColorSpaceRef cs = CGColorSpaceCreateDeviceGray();
                CGContextRef cg = CGBitmapContextCreate(
                    gray.data(), bw, bh, 8, bw, cs, kCGImageAlphaNone);
                if (cg) {
                    CGContextSetGrayFillColor(cg, 1.0, 1.0);
                    CGPoint pos = CGPointMake(-static_cast<CGFloat>(x0), -static_cast<CGFloat>(y0));
                    CTFontDrawGlyphs(font, &glyph, &pos, 1, cg);
                    CGContextRelease(cg);
                }
                CGColorSpaceRelease(cs);
            }
        }
        CFRelease(font);
    }
#endif

    if (gray.empty()) {
        bw = 1u; bh = 1u;
        gray.assign(1u, 0u);
    }

    if (gm_va) {
        mem.w32(gm_va + 0u, bw);
        mem.w32(gm_va + 4u, bh);
        mem.w32(gm_va + 8u, static_cast<uint32_t>(origin_x));
        mem.w32(gm_va + 12u, static_cast<uint32_t>(origin_y));
        mem.w16(gm_va + 16u, static_cast<uint16_t>(adv_x));
        mem.w16(gm_va + 18u, 0u);
    }

    if (format == 0u) { // GGO_METRICS
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 28u);
        return;
    }

    const bool is_mono = (format == 1u);
    const uint32_t gray_max = (format == 4u) ? 4u : ((format == 5u) ? 16u : 64u);
    const uint32_t stride = is_mono ? (((bw + 31u) / 32u) * 4u) : (((bw + 3u) / 4u) * 4u);
    const uint32_t needed = stride * bh;

    if (buf_va != 0u && cb_buf >= needed) {
        mem.zero_bytes(buf_va, needed);
        for (uint32_t y = 0; y < bh; ++y) {
            for (uint32_t x = 0; x < bw; ++x) {
                const uint8_t px = gray[y * bw + x];
                if (is_mono) {
                    if (px >= 128u) {
                        const uint32_t byte_off = y * stride + (x >> 3);
                        const uint8_t mask = static_cast<uint8_t>(0x80u >> (x & 7u));
                        mem.w8(buf_va + byte_off, mem.r8(buf_va + byte_off) | mask);
                    }
                } else {
                    const uint8_t gval = static_cast<uint8_t>((static_cast<uint32_t>(px) * gray_max + 127u) / 255u);
                    mem.w8(buf_va + y * stride + x, gval);
                }
            }
        }
    }

    ctx.eax = needed;
    ctx.ret_stdcall(mem, 28u);
}

// ---------------------------------------------------------------------------
// SHLWAPI Path Helpers
// ---------------------------------------------------------------------------
void shlw_path_find_filename_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t p_va = ctx.arg32(mem, 0);
    const std::string s = mem.read_cstring(p_va);
    const size_t pos = s.find_last_of("/\\");
    ctx.eax = (pos == std::string::npos) ? p_va : (p_va + static_cast<uint32_t>(pos + 1u));
    ctx.ret_stdcall(mem, 4u);
}

void shlw_path_file_exists_a(CpuContext& ctx, GuestMemory& mem) {
    bool exists = false;
    resolve_asset_path(mem.read_cstring(ctx.arg32(mem, 0)), false, &exists);
    ctx.eax = exists ? 1u : 0u;
    ctx.ret_stdcall(mem, 4u);
}

void shlw_path_remove_extension_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t p_va = ctx.arg32(mem, 0);
    std::string s = mem.read_cstring(p_va);
    const size_t slash = s.find_last_of("/\\");
    const size_t dot = s.find_last_of('.');
    if (dot != std::string::npos && (slash == std::string::npos || dot > slash)) {
        mem.w8(p_va + static_cast<uint32_t>(dot), 0u);
    }
    ctx.ret_stdcall(mem, 4u);
}

void shlw_path_remove_filespec_a(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t p_va = ctx.arg32(mem, 0);
    std::string s = mem.read_cstring(p_va);
    const size_t slash = s.find_last_of("/\\");
    if (slash != std::string::npos) {
        mem.w8(p_va + static_cast<uint32_t>(slash), 0u);
        ctx.eax = 1u;
    } else {
        ctx.eax = 0u;
    }
    ctx.ret_stdcall(mem, 4u);
}

void shlw_path_is_directory_a(CpuContext& ctx, GuestMemory& mem) {
    bool exists = false;
    const fs::path p = resolve_asset_path(mem.read_cstring(ctx.arg32(mem, 0)), false, &exists);
    std::error_code ec;
    ctx.eax = (exists && fs::is_directory(p, ec)) ? 1u : 0u;
    ctx.ret_stdcall(mem, 4u);
}

// ---------------------------------------------------------------------------
// WS2_32 BSD Socket Shims (22 imports)
// ---------------------------------------------------------------------------
#if !defined(_WIN32)
void fill_host_sockaddr(const GuestMemory& mem, uint32_t sa_va, sockaddr_in& out) {
    std::memset(&out, 0, sizeof(out));
    out.sin_family = AF_INET;
    out.sin_port   = htons(static_cast<uint16_t>((mem.r8(sa_va + 2u) << 8) | mem.r8(sa_va + 3u)));
    std::memcpy(&out.sin_addr.s_addr, mem.cptr(sa_va + 4u), 4);
}

void write_guest_sockaddr(GuestMemory& mem, uint32_t sa_va, const sockaddr_in& in) {
    mem.zero_bytes(sa_va, 16u);
    mem.w16(sa_va + 0u, 2u); // AF_INET
    std::memcpy(mem.ptr(sa_va + 2u), &in.sin_port, 2);
    std::memcpy(mem.ptr(sa_va + 4u), &in.sin_addr.s_addr, 4);
}
#endif

void ws2_socket(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int af = (ctx.arg32(mem, 0) == 2u) ? AF_INET : static_cast<int>(ctx.arg32(mem, 0));
    const int ty = (ctx.arg32(mem, 1) == 2u) ? SOCK_DGRAM : SOCK_STREAM;
    const int pr = static_cast<int>(ctx.arg32(mem, 2));
    const int fd = ::socket(af, ty, pr);
    if (fd < 0) {
        g_w32.last_wsa_error.store(errno, std::memory_order_relaxed);
        ctx.eax = 0xFFFFFFFFu;
    } else {
#if defined(SO_NOSIGPIPE)
        int nosig = 1;
        ::setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &nosig, sizeof(nosig));
#endif
        ctx.eax = static_cast<uint32_t>(fd);
    }
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 12u);
}

void ws2_bind(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t sa_va = ctx.arg32(mem, 1);
    sockaddr_in sa{};
    fill_host_sockaddr(mem, sa_va, sa);
    const int rc = ::bind(fd, reinterpret_cast<const sockaddr*>(&sa), sizeof(sa));
    if (rc < 0) g_w32.last_wsa_error.store(errno, std::memory_order_relaxed);
    ctx.eax = static_cast<uint32_t>(rc);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 12u);
}

void ws2_connect(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    sockaddr_in sa{};
    fill_host_sockaddr(mem, ctx.arg32(mem, 1), sa);

    const int orig_flags = ::fcntl(fd, F_GETFL, 0);
    const bool was_blocking = (orig_flags >= 0) && ((orig_flags & O_NONBLOCK) == 0);
    if (was_blocking) {
        ::fcntl(fd, F_SETFL, orig_flags | O_NONBLOCK);
    }

    int rc = ::connect(fd, reinterpret_cast<const sockaddr*>(&sa), sizeof(sa));
    if (rc < 0 && was_blocking && errno == EINPROGRESS) {
        constexpr int kConnectBudgetMs = 2500;
        int waited_ms = 0;
        bool connected = false;
        while (waited_ms < kConnectBudgetMs) {
            if (g_w32.quit_requested.load(std::memory_order_acquire)) {
                g_w32.last_wsa_error.store(10054, std::memory_order_relaxed); // WSAECONNRESET
                break;
            }
            struct pollfd pfd{};
            pfd.fd = fd;
            pfd.events = POLLOUT;
            const int prc = ::poll(&pfd, 1, 50);
            if (prc > 0) {
                int so_err = 0;
                socklen_t so_len = sizeof(so_err);
                if (::getsockopt(fd, SOL_SOCKET, SO_ERROR, &so_err, &so_len) == 0 && so_err == 0) {
                    connected = true;
                    rc = 0;
                } else {
                    g_w32.last_wsa_error.store(so_err ? so_err : 10061, std::memory_order_relaxed);
                }
                break;
            }
            if (prc < 0 && errno != EINTR) {
                g_w32.last_wsa_error.store(errno, std::memory_order_relaxed);
                break;
            }
            waited_ms += 50;
        }
        if (!connected && rc < 0 && waited_ms >= kConnectBudgetMs) {
            g_w32.last_wsa_error.store(10060, std::memory_order_relaxed); // WSAETIMEDOUT
        }
    } else if (rc < 0) {
        const int err = (errno == EINPROGRESS || errno == EAGAIN || errno == EWOULDBLOCK) ? 10035 : errno;
        g_w32.last_wsa_error.store(err, std::memory_order_relaxed);
    }

    if (was_blocking) {
        ::fcntl(fd, F_SETFL, orig_flags);
    }
    ctx.eax = static_cast<uint32_t>(rc);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 12u);
}

void ws2_listen(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int rc = ::listen(static_cast<int>(ctx.arg32(mem, 0)), static_cast<int>(ctx.arg32(mem, 1)));
    ctx.eax = static_cast<uint32_t>(rc);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 8u);
}

void ws2_accept(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t sa_va = ctx.arg32(mem, 1);
    const uint32_t len_va = ctx.arg32(mem, 2);
    sockaddr_in sa{};
    socklen_t sl = sizeof(sa);
    const int cfd = ::accept(fd, sa_va ? reinterpret_cast<sockaddr*>(&sa) : nullptr, sa_va ? &sl : nullptr);
    if (cfd >= 0 && sa_va) write_guest_sockaddr(mem, sa_va, sa);
    if (cfd >= 0 && len_va) mem.w32(len_va, 16u);
    ctx.eax = static_cast<uint32_t>(cfd);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 12u);
}

void ws2_send(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t buf_va = ctx.arg32(mem, 1);
    const int len = static_cast<int>(ctx.arg32(mem, 2));
    const int flags = static_cast<int>(ctx.arg32(mem, 3));
    const ssize_t rc = ::send(fd, mem.cptr(buf_va), static_cast<size_t>(std::max(0, len)), flags);
    if (rc < 0) g_w32.last_wsa_error.store(errno, std::memory_order_relaxed);
    ctx.eax = static_cast<uint32_t>(rc);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 16u);
}

void ws2_sendto(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t buf_va = ctx.arg32(mem, 1);
    const int len = static_cast<int>(ctx.arg32(mem, 2));
    const int flags = static_cast<int>(ctx.arg32(mem, 3));
    const uint32_t sa_va = ctx.arg32(mem, 4);
    sockaddr_in sa{};
    fill_host_sockaddr(mem, sa_va, sa);
    const ssize_t rc = ::sendto(fd, mem.cptr(buf_va), static_cast<size_t>(std::max(0, len)),
                                flags, reinterpret_cast<const sockaddr*>(&sa), sizeof(sa));
    if (rc < 0) g_w32.last_wsa_error.store(errno, std::memory_order_relaxed);
    ctx.eax = static_cast<uint32_t>(rc);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 24u);
}

void ws2_recv(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t buf_va = ctx.arg32(mem, 1);
    const int len = static_cast<int>(ctx.arg32(mem, 2));
    const int flags = static_cast<int>(ctx.arg32(mem, 3));
    const ssize_t rc = ::recv(fd, mem.ptr(buf_va), static_cast<size_t>(std::max(0, len)), flags);
    if (rc < 0) g_w32.last_wsa_error.store((errno == EAGAIN || errno == EWOULDBLOCK) ? 10035 : errno,
                                            std::memory_order_relaxed);
    ctx.eax = static_cast<uint32_t>(rc);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 16u);
}

void ws2_recvfrom(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t buf_va = ctx.arg32(mem, 1);
    const int len = static_cast<int>(ctx.arg32(mem, 2));
    const int flags = static_cast<int>(ctx.arg32(mem, 3));
    const uint32_t sa_va = ctx.arg32(mem, 4);
    const uint32_t sl_va = ctx.arg32(mem, 5);
    sockaddr_in sa{};
    socklen_t sl = sizeof(sa);
    const ssize_t rc = ::recvfrom(fd, mem.ptr(buf_va), static_cast<size_t>(std::max(0, len)),
                                  flags, sa_va ? reinterpret_cast<sockaddr*>(&sa) : nullptr,
                                  sa_va ? &sl : nullptr);
    if (rc >= 0 && sa_va) write_guest_sockaddr(mem, sa_va, sa);
    if (rc >= 0 && sl_va) mem.w32(sl_va, 16u);
    if (rc < 0) g_w32.last_wsa_error.store((errno == EAGAIN || errno == EWOULDBLOCK) ? 10035 : errno,
                                            std::memory_order_relaxed);
    ctx.eax = static_cast<uint32_t>(rc);
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 24u);
}

void ws2_wsa_recv(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd            = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t bufs_va  = ctx.arg32(mem, 1);
    const uint32_t cnt      = ctx.arg32(mem, 2);
    const uint32_t recvd_va = ctx.arg32(mem, 3);
    const uint32_t flags_va = ctx.arg32(mem, 4);
    const uint32_t ovl_va   = ctx.arg32(mem, 5);
    const uint32_t comp_va  = ctx.arg32(mem, 6);

    if (fd >= 0 && cnt > 0u && bufs_va != 0u && mem.in_bounds(bufs_va, 8u)) {
        const uint32_t len = mem.r32(bufs_va + 0u);
        const uint32_t pva = mem.r32(bufs_va + 4u);
        uint8_t* dst = mem.ptr(pva);
        if (!dst || !mem.in_bounds(pva, len)) {
            g_w32.last_wsa_error.store(10014, std::memory_order_relaxed); // WSAEFAULT
            ctx.eax = 0xFFFFFFFFu;
            ctx.ret_stdcall(mem, 28u);
            return;
        }

        const int fd_flags = ::fcntl(fd, F_GETFL, 0);
        const bool is_nonblock = (fd_flags >= 0) && ((fd_flags & O_NONBLOCK) != 0);
        if (!is_nonblock) {
            constexpr int kRecvBudgetMs = 2500;
            int waited_ms = 0;
            bool ready = false;
            while (waited_ms < kRecvBudgetMs) {
                if (g_w32.quit_requested.load(std::memory_order_acquire)) {
                    g_w32.last_wsa_error.store(10054, std::memory_order_relaxed); // WSAECONNRESET
                    ctx.eax = 0xFFFFFFFFu;
                    ctx.ret_stdcall(mem, 28u);
                    return;
                }
                struct pollfd pfd{};
                pfd.fd = fd;
                pfd.events = POLLIN;
                const int prc = ::poll(&pfd, 1, 50);
                if (prc > 0) {
                    ready = true;
                    break;
                }
                if (prc < 0 && errno != EINTR) {
                    g_w32.last_wsa_error.store(10054, std::memory_order_relaxed);
                    ctx.eax = 0xFFFFFFFFu;
                    ctx.ret_stdcall(mem, 28u);
                    return;
                }
                waited_ms += 50;
            }
            if (!ready) {
                g_w32.last_wsa_error.store(10060, std::memory_order_relaxed); // WSAETIMEDOUT
                ctx.eax = 0xFFFFFFFFu;
                ctx.ret_stdcall(mem, 28u);
                return;
            }
        }

        ssize_t rc = -1;
        do {
            rc = ::recv(fd, dst, len, 0);
        } while (rc < 0 && errno == EINTR && !g_w32.quit_requested.load(std::memory_order_acquire));

        if (rc >= 0) {
            const uint32_t bytes = static_cast<uint32_t>(rc);
            if (recvd_va != 0u && mem.in_bounds(recvd_va, 4u)) {
                mem.w32(recvd_va, bytes);
            }
            if (ovl_va != 0u && mem.in_bounds(ovl_va, 20u)) {
                mem.w32(ovl_va + 0u, 0u);    // Internal = STATUS_SUCCESS
                mem.w32(ovl_va + 4u, bytes); // InternalHigh = cbTransferred
                if (comp_va == 0u) {
                    const uint32_t ev = mem.r32(ovl_va + 16u);
                    if (ev != 0u) hle_win32_signal_event(ev);
                }
            }
            if (comp_va != 0u) {
                const uint32_t in_flags = (flags_va != 0u && mem.in_bounds(flags_va, 4u)) ? mem.r32(flags_va) : 0u;
                PendingApc apc;
                apc.fn_va          = comp_va;
                apc.dw_error       = 0u;
                apc.cb_transferred = bytes;
                apc.lp_overlapped  = ovl_va;
                apc.dw_flags       = in_flags;
                tls_pending_apcs.push_back(apc);
            }
            ctx.eax = 0u;
            ctx.ret_stdcall(mem, 28u);
            return;
        }
        g_w32.last_wsa_error.store(
            (errno == EAGAIN || errno == EWOULDBLOCK) ? 10035 : 10054,
            std::memory_order_relaxed);
    } else {
        g_w32.last_wsa_error.store(10022, std::memory_order_relaxed); // WSAEINVAL
    }
    ctx.eax = 0xFFFFFFFFu;
#else
    g_w32.last_wsa_error.store(10054, std::memory_order_relaxed);
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 28u);
}

void ws2_closesocket(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    ctx.eax = static_cast<uint32_t>(::close(static_cast<int>(ctx.arg32(mem, 0))));
#else
    ctx.eax = 0u;
#endif
    ctx.ret_stdcall(mem, 4u);
}

void ws2_shutdown(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    ctx.eax = static_cast<uint32_t>(::shutdown(static_cast<int>(ctx.arg32(mem, 0)),
                                               static_cast<int>(ctx.arg32(mem, 1))));
#else
    ctx.eax = 0u;
#endif
    ctx.ret_stdcall(mem, 8u);
}

void ws2_htons_ntohs(CpuContext& ctx, GuestMemory& mem) {
    const uint16_t v = static_cast<uint16_t>(ctx.arg32(mem, 0) & 0xFFFFu);
    ctx.eax = static_cast<uint16_t>(((v & 0xFFu) << 8) | ((v >> 8) & 0xFFu));
    ctx.ret_stdcall(mem, 4u);
}

void ws2_inet_addr(CpuContext& ctx, GuestMemory& mem) {
    const std::string ip = mem.read_cstring(ctx.arg32(mem, 0));
#if !defined(_WIN32)
    ctx.eax = ::inet_addr(ip.c_str());
#else
    ctx.eax = 0xFFFFFFFFu;
#endif
    ctx.ret_stdcall(mem, 4u);
}

void ws2_inet_ntoa(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t addr = ctx.arg32(mem, 0);
    if (g_w32.temp_str_va == 0u) g_w32.temp_str_va = mem.alloc_thunk_block(64u, 4u);
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%u.%u.%u.%u",
                  addr & 0xFFu, (addr >> 8) & 0xFFu, (addr >> 16) & 0xFFu, (addr >> 24) & 0xFFu);
    mem.write_cstring(g_w32.temp_str_va, buf, 64u);
    ctx.eax = g_w32.temp_str_va;
    ctx.ret_stdcall(mem, 4u);
}

void ws2_gethostbyname(CpuContext& ctx, GuestMemory& mem) {
    const std::string name = mem.read_cstring(ctx.arg32(mem, 0));
    const std::string low  = ascii_lower(name);
    const bool is_local_name = low.empty() || low == "localhost" || low == "iphone-se-2020";

    uint32_t ip_be = 0x0100007Fu; // 127.0.0.1 for local host fallback
    bool resolved = is_local_name;
#if !defined(_WIN32)
    if (!name.empty()) {
        struct addrinfo hints{};
        hints.ai_family = AF_INET;
        struct addrinfo* res = nullptr;
        if (::getaddrinfo(name.c_str(), nullptr, &hints, &res) == 0 && res != nullptr) {
            auto* sin = reinterpret_cast<sockaddr_in*>(res->ai_addr);
            std::memcpy(&ip_be, &sin->sin_addr.s_addr, 4);
            ::freeaddrinfo(res);
            resolved = true;
        }
    }
#endif
    if (!resolved) {
        g_w32.last_wsa_error.store(11001, std::memory_order_relaxed); // WSAHOST_NOT_FOUND
        ctx.eax = 0u;
        ctx.ret_stdcall(mem, 4u);
        return;
    }
    if (g_w32.hostent_va == 0u) g_w32.hostent_va = mem.alloc_thunk_block(128u, 8u);
    const uint32_t he   = g_w32.hostent_va;
    const uint32_t ipva = he + 32u;
    const uint32_t arr  = he + 40u;
    const uint32_t nmva = he + 56u;
    mem.w32(ipva, ip_be);
    mem.w32(arr + 0u, ipva);
    mem.w32(arr + 4u, 0u);
    mem.write_cstring(nmva, name, 64u);
    mem.w32(he + 0u, nmva);
    mem.w32(he + 4u, arr + 4u);
    mem.w16(he + 8u, 2u); // AF_INET
    mem.w16(he + 10u, 4u);
    mem.w32(he + 12u, arr);
    ctx.eax = he;
    ctx.ret_stdcall(mem, 4u);
}

void ws2_wsa_async_select(CpuContext& ctx, GuestMemory& mem) {
#if !defined(_WIN32)
    const int fd = static_cast<int>(ctx.arg32(mem, 0));
    const uint32_t l_event = ctx.arg32(mem, 3);
    int flags = ::fcntl(fd, F_GETFL, 0);
    if (flags >= 0) {
        if (l_event != 0u) ::fcntl(fd, F_SETFL, flags | O_NONBLOCK);
        else ::fcntl(fd, F_SETFL, flags & ~O_NONBLOCK);
    }
#endif
    ctx.eax = 0u;
    ctx.ret_stdcall(mem, 16u);
}

void ws2_get_last_error(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = static_cast<uint32_t>(g_w32.last_wsa_error.load(std::memory_order_relaxed));
    ctx.ret_stdcall(mem, 0u);
}

// ---------------------------------------------------------------------------
// ole32 / OLEAUT32 / D3D9 / Generic Return Helpers
// ---------------------------------------------------------------------------
void ole32_co_create_instance(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t rclsid_va = ctx.arg32(mem, 0);
    const uint32_t riid_va   = ctx.arg32(mem, 3);
    const uint32_t ppv_va    = ctx.arg32(mem, 4);
    if (ppv_va == 0u) {
        ctx.eax = 0x80004003u;
        ctx.ret_stdcall(mem, 20u);
        return;
    }

    uint8_t clsid[16] = {};
    uint8_t iid[16] = {};
    if (rclsid_va) mem.read_bytes(rclsid_va, clsid, 16);
    if (riid_va) mem.read_bytes(riid_va, iid, 16);

    uint32_t out_iface = 0u;
    if (hle_dshow_try_cocreate(mem, clsid, iid, &out_iface)) {
        mem.w32(ppv_va, out_iface);
        ctx.eax = 0u; // S_OK
    } else {
        mem.w32(ppv_va, 0u);
        ctx.eax = 0x80040154u; // REGDB_E_CLASSNOTREG (cleanly handled by DxDiag/etc.)
    }
    ctx.ret_stdcall(mem, 20u);
}

void oleaut_variant_init(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pvarg = ctx.arg32(mem, 0);
    if (pvarg) mem.zero_bytes(pvarg, 16u);
    ctx.ret_stdcall(mem, 4u);
}

void oleaut_variant_clear(CpuContext& ctx, GuestMemory& mem) {
    const uint32_t pvarg = ctx.arg32(mem, 0);
    if (pvarg) mem.zero_bytes(pvarg, 16u);
    ctx.eax = 0u;
    ctx.ret_stdcall(mem, 4u);
}

template <uint32_t ArgBytes, uint32_t RetVal = 0u>
void win32_ret_val(CpuContext& ctx, GuestMemory& mem) {
    ctx.eax = RetVal;
    ctx.ret_stdcall(mem, ArgBytes);
}

template <uint32_t ArgBytes>
void win32_ret_void(CpuContext& ctx, GuestMemory& mem) {
    ctx.ret_stdcall(mem, ArgBytes);
}

void d3d_iat_forward(CpuContext& ctx, GuestMemory& mem, uint32_t iat_va, const char* name) {
    if (auto fn = detail::g_d3d_iat_handler.load(std::memory_order_acquire); fn != nullptr) {
        fn(iat_va, name, ctx, mem);
        return;
    }
    if (auto* bridge = D3D9MetalBridge::active(); bridge != nullptr) {
        if (bridge->handle_d3d_iat(iat_va, name, ctx, mem)) {
            return;
        }
    }
    std::fprintf(stderr, "[hle_win32] D3D9/D3DX9 call %s (0x%08x) with no Metal bridge registered\n", name, iat_va);
    ctx.eax = 0u;
    ctx.ret_stdcall(mem, 4u);
}

using IatFn = void (*)(CpuContext&, GuestMemory&);

struct IatDescriptor {
    uint32_t    va;
    const char* name;
    IatFn       fn;
};

// Complete table of all 247 IAT VAs in MBAA.exe (0x0051B000..0x0051B408), strictly sorted by VA.
constexpr IatDescriptor kIatTable[] = {
    {0x0051B000u, "DINPUT8.dll!DirectInput8Create", &hle_direct_input8_create},
    {0x0051B008u, "DSOUND.dll!DirectSoundCreate8", &hle_direct_sound_create8},
    {0x0051B010u, "GDI32.dll!SelectObject", &gdi_select_object},
    {0x0051B014u, "GDI32.dll!GetGlyphOutlineA", &gdi_get_glyph_outline_a},
    {0x0051B018u, "GDI32.dll!CreateFontIndirectA", &gdi_create_font_indirect_a},
    {0x0051B01Cu, "GDI32.dll!DeleteObject", &win32_ret_val<4u, 1u>},
    {0x0051B020u, "GDI32.dll!GetTextMetricsA", &gdi_get_text_metrics_a},
    {0x0051B024u, "GDI32.dll!GetStockObject", &win32_ret_val<4u, 0x10000010u>},
    {0x0051B02Cu, "KERNEL32.dll!WritePrivateProfileStringA", &k32_write_private_profile_string_a},
    {0x0051B030u, "KERNEL32.dll!GetLastError", &k32_get_last_error},
    {0x0051B034u, "KERNEL32.dll!ReleaseMutex", &k32_release_mutex},
    {0x0051B038u, "KERNEL32.dll!CreateMutexA", &k32_create_mutex_a},
    {0x0051B03Cu, "KERNEL32.dll!WaitForMultipleObjects", &k32_wait_multiple},
    {0x0051B040u, "KERNEL32.dll!WaitForSingleObject", &k32_wait_single},
    {0x0051B044u, "KERNEL32.dll!SetEvent", &k32_set_event},
    {0x0051B048u, "KERNEL32.dll!CreateEventA", &k32_create_event_a},
    {0x0051B04Cu, "KERNEL32.dll!ReadFile", &k32_read_file},
    {0x0051B050u, "KERNEL32.dll!ExitThread", &k32_exit_thread},
    {0x0051B054u, "KERNEL32.dll!CreateFileA", &k32_create_file_a},
    {0x0051B058u, "KERNEL32.dll!GetFileSize", &k32_get_file_size},
    {0x0051B05Cu, "KERNEL32.dll!UnmapViewOfFile", &win32_ret_val<4u, 1u>},
    {0x0051B060u, "KERNEL32.dll!GetModuleHandleA", &k32_get_module_handle_a},
    {0x0051B064u, "KERNEL32.dll!DeleteCriticalSection", &k32_delete_crit_sec},
    {0x0051B068u, "KERNEL32.dll!InitializeCriticalSection", &k32_init_crit_sec},
    {0x0051B06Cu, "KERNEL32.dll!MultiByteToWideChar", &k32_multibyte_to_widechar},
    {0x0051B070u, "KERNEL32.dll!LeaveCriticalSection", &k32_leave_crit_sec},
    {0x0051B074u, "KERNEL32.dll!InterlockedIncrement", &k32_interlocked_inc},
    {0x0051B078u, "KERNEL32.dll!EnterCriticalSection", &k32_enter_crit_sec},
    {0x0051B07Cu, "KERNEL32.dll!InterlockedDecrement", &k32_interlocked_dec},
    {0x0051B080u, "KERNEL32.dll!CreateDirectoryA", &k32_create_directory_a},
    {0x0051B084u, "KERNEL32.dll!FindClose", &k32_find_close},
    {0x0051B088u, "KERNEL32.dll!WideCharToMultiByte", &k32_widechar_to_multibyte},
    {0x0051B08Cu, "KERNEL32.dll!FindFirstFileA", &k32_find_first_file_a},
    {0x0051B090u, "KERNEL32.dll!ResetEvent", &k32_reset_event},
    {0x0051B094u, "KERNEL32.dll!SetFilePointer", &k32_set_file_pointer},
    {0x0051B098u, "KERNEL32.dll!FindNextFileA", &k32_find_next_file_a},
    {0x0051B09Cu, "KERNEL32.dll!GetOverlappedResult", &k32_get_overlapped_result},
    {0x0051B0A0u, "KERNEL32.dll!GetDiskFreeSpaceA", &k32_get_disk_free_space_a},
    {0x0051B0A4u, "KERNEL32.dll!DeleteFileA", &k32_delete_file_a},
    {0x0051B0A8u, "KERNEL32.dll!GetFileAttributesA", &k32_get_file_attributes_a},
    {0x0051B0ACu, "KERNEL32.dll!WriteFile", &k32_write_file},
    {0x0051B0B0u, "KERNEL32.dll!GetLocalTime", &k32_get_local_time},
    {0x0051B0B4u, "KERNEL32.dll!GlobalLock", &k32_global_lock},
    {0x0051B0B8u, "KERNEL32.dll!GlobalAlloc", &k32_global_alloc},
    {0x0051B0BCu, "KERNEL32.dll!GlobalUnlock", &k32_global_unlock},
    {0x0051B0C0u, "KERNEL32.dll!GetFileTime", &win32_ret_val<16u, 1u>},
    {0x0051B0C4u, "KERNEL32.dll!FileTimeToLocalFileTime", &win32_ret_val<8u, 1u>},
    {0x0051B0C8u, "KERNEL32.dll!FileTimeToSystemTime", &win32_ret_val<8u, 1u>},
    {0x0051B0CCu, "KERNEL32.dll!HeapAlloc", &k32_heap_alloc},
    {0x0051B0D0u, "KERNEL32.dll!GetProcessHeap", &win32_ret_val<0u, 0x10000008u>},
    {0x0051B0D4u, "KERNEL32.dll!HeapFree", &k32_heap_free},
    {0x0051B0D8u, "KERNEL32.dll!ReleaseSemaphore", &k32_release_semaphore},
    {0x0051B0DCu, "KERNEL32.dll!CreateSemaphoreA", &k32_create_semaphore_a},
    {0x0051B0E0u, "KERNEL32.dll!SleepEx", &k32_sleep_ex},
    {0x0051B0E4u, "KERNEL32.dll!GetModuleFileNameA", &k32_get_module_filename_a},
    {0x0051B0E8u, "KERNEL32.dll!FreeLibrary", &win32_ret_val<4u, 1u>},
    {0x0051B0ECu, "KERNEL32.dll!GetTickCount", &k32_get_tick_count},
    {0x0051B0F0u, "KERNEL32.dll!GetProcAddress", &win32_ret_val<8u, 0u>},
    {0x0051B0F4u, "KERNEL32.dll!LoadLibraryA", &k32_load_library_a},
    {0x0051B0F8u, "KERNEL32.dll!GetConsoleOutputCP", &win32_ret_val<0u, 932u>},
    {0x0051B0FCu, "KERNEL32.dll!WriteConsoleA", &win32_ret_val<20u, 1u>},
    {0x0051B100u, "KERNEL32.dll!FlushFileBuffers", &win32_ret_val<4u, 1u>},
    {0x0051B104u, "KERNEL32.dll!SetStdHandle", &win32_ret_val<8u, 1u>},
    {0x0051B108u, "KERNEL32.dll!GetLocaleInfoA", &win32_ret_val<16u, 0u>},
    {0x0051B10Cu, "KERNEL32.dll!GetStringTypeW", &win32_ret_val<16u, 1u>},
    {0x0051B110u, "KERNEL32.dll!GetStringTypeA", &win32_ret_val<20u, 1u>},
    {0x0051B114u, "KERNEL32.dll!GetConsoleMode", &win32_ret_val<8u, 0u>},
    {0x0051B118u, "KERNEL32.dll!GetConsoleCP", &win32_ret_val<0u, 932u>},
    {0x0051B11Cu, "KERNEL32.dll!GetCurrentProcessId", &win32_ret_val<0u, 0x1000u>},
    {0x0051B120u, "KERNEL32.dll!GetEnvironmentStringsW", &k32_get_env_strings_w},
    {0x0051B124u, "KERNEL32.dll!FreeEnvironmentStringsW", &win32_ret_val<4u, 1u>},
    {0x0051B128u, "KERNEL32.dll!GetEnvironmentStrings", &k32_get_env_strings_a},
    {0x0051B12Cu, "KERNEL32.dll!FreeEnvironmentStringsA", &win32_ret_val<4u, 1u>},
    {0x0051B130u, "KERNEL32.dll!LCMapStringW", &win32_ret_val<24u, 0u>},
    {0x0051B134u, "KERNEL32.dll!LCMapStringA", &win32_ret_val<24u, 0u>},
    {0x0051B138u, "KERNEL32.dll!GetFileType", &win32_ret_val<4u, 1u>},
    {0x0051B13Cu, "KERNEL32.dll!SetHandleCount", &win32_ret_val<4u, 32u>},
    {0x0051B140u, "KERNEL32.dll!GetTimeZoneInformation", &win32_ret_val<4u, 0u>},
    {0x0051B144u, "KERNEL32.dll!IsValidCodePage", &win32_ret_val<4u, 1u>},
    {0x0051B148u, "KERNEL32.dll!GetOEMCP", &win32_ret_val<0u, 932u>},
    {0x0051B14Cu, "KERNEL32.dll!GetACP", &win32_ret_val<0u, 932u>},
    {0x0051B150u, "KERNEL32.dll!GetCPInfo", &win32_ret_val<8u, 1u>},
    {0x0051B154u, "KERNEL32.dll!HeapSize", &k32_heap_size},
    {0x0051B158u, "KERNEL32.dll!SetLastError", &k32_set_last_error},
    {0x0051B15Cu, "KERNEL32.dll!TlsFree", &k32_tls_free},
    {0x0051B160u, "KERNEL32.dll!TlsSetValue", &k32_tls_set_value},
    {0x0051B164u, "KERNEL32.dll!TlsAlloc", &k32_tls_alloc},
    {0x0051B168u, "KERNEL32.dll!TlsGetValue", &k32_tls_get_value},
    {0x0051B16Cu, "KERNEL32.dll!GetStdHandle", &win32_ret_val<4u, 0x10000011u>},
    {0x0051B170u, "KERNEL32.dll!VirtualAlloc", &k32_virtual_alloc},
    {0x0051B174u, "KERNEL32.dll!RtlUnwind", &win32_ret_void<16u>},
    {0x0051B178u, "KERNEL32.dll!RaiseException", &win32_ret_void<16u>},
    {0x0051B17Cu, "KERNEL32.dll!GetStartupInfoA", &win32_ret_void<4u>},
    {0x0051B180u, "KERNEL32.dll!GetVersionExA", &k32_get_version_ex_a},
    {0x0051B184u, "KERNEL32.dll!GetCommandLineA", &k32_get_command_line_a},
    {0x0051B188u, "KERNEL32.dll!GetDateFormatA", &win32_ret_val<24u, 0u>},
    {0x0051B18Cu, "KERNEL32.dll!GetTimeFormatA", &win32_ret_val<24u, 0u>},
    {0x0051B190u, "KERNEL32.dll!SetEnvironmentVariableA", &win32_ret_val<8u, 1u>},
    {0x0051B194u, "KERNEL32.dll!GetCurrentThreadId", [](CpuContext& c, GuestMemory& m){ c.eax = current_tid(); c.ret_stdcall(m, 0u); }},
    {0x0051B198u, "KERNEL32.dll!GetSystemTimeAsFileTime", &k32_get_system_time_as_file_time},
    {0x0051B19Cu, "KERNEL32.dll!HeapReAlloc", &k32_heap_realloc},
    {0x0051B1A0u, "KERNEL32.dll!ExitProcess", [](CpuContext& c, GuestMemory& m){ const int ec = static_cast<int>(c.arg32(m, 0)); hle_win32_log("ExitProcess(%d)", ec); hle_win32_post_quit(ec); c.ret_stdcall(m, 4u); }},
    {0x0051B1A4u, "KERNEL32.dll!VirtualFree", &k32_virtual_free},
    {0x0051B1A8u, "KERNEL32.dll!HeapCreate", &win32_ret_val<12u, 0x10000009u>},
    {0x0051B1ACu, "KERNEL32.dll!HeapDestroy", &win32_ret_val<4u, 1u>},
    {0x0051B1B0u, "KERNEL32.dll!IsDebuggerPresent", &win32_ret_val<0u, 0u>},
    {0x0051B1B4u, "KERNEL32.dll!SetUnhandledExceptionFilter", &win32_ret_val<4u, 0u>},
    {0x0051B1B8u, "KERNEL32.dll!UnhandledExceptionFilter", &win32_ret_val<4u, 0u>},
    {0x0051B1BCu, "KERNEL32.dll!GetCurrentProcess", &win32_ret_val<0u, 0xFFFFFFFFu>},
    {0x0051B1C0u, "KERNEL32.dll!TerminateProcess", &win32_ret_val<8u, 1u>},
    {0x0051B1C4u, "KERNEL32.dll!WaitForSingleObjectEx", &k32_wait_single_ex},
    {0x0051B1C8u, "KERNEL32.dll!CreateThread", &k32_create_thread},
    {0x0051B1CCu, "KERNEL32.dll!CloseHandle", &k32_close_handle},
    {0x0051B1D0u, "KERNEL32.dll!Sleep", &k32_sleep},
    {0x0051B1D4u, "KERNEL32.dll!QueryPerformanceCounter", &k32_query_performance_counter},
    {0x0051B1D8u, "KERNEL32.dll!QueryPerformanceFrequency", &k32_query_performance_frequency},
    {0x0051B1DCu, "KERNEL32.dll!WriteConsoleW", &win32_ret_val<20u, 1u>},
    {0x0051B1E0u, "KERNEL32.dll!CompareStringA", &k32_compare_string_a},
    {0x0051B1E4u, "KERNEL32.dll!GetComputerNameA", &k32_get_computer_name_a},
    {0x0051B1E8u, "KERNEL32.dll!CompareStringW", &k32_compare_string_w},
    {0x0051B1F0u, "OLEAUT32.dll!VariantClear", &oleaut_variant_clear},
    {0x0051B1F4u, "OLEAUT32.dll!VariantInit", &oleaut_variant_init},
    {0x0051B1FCu, "SHELL32.dll!ShellExecuteA", &win32_ret_val<24u, 33u>},
    {0x0051B204u, "SHLWAPI.dll!PathFindFileNameA", &shlw_path_find_filename_a},
    {0x0051B208u, "SHLWAPI.dll!PathFileExistsA", &shlw_path_file_exists_a},
    {0x0051B20Cu, "SHLWAPI.dll!PathRemoveExtensionA", &shlw_path_remove_extension_a},
    {0x0051B210u, "SHLWAPI.dll!PathRemoveFileSpecA", &shlw_path_remove_filespec_a},
    {0x0051B214u, "SHLWAPI.dll!PathIsDirectoryA", &shlw_path_is_directory_a},
    {0x0051B21Cu, "USER32.dll!RegisterClassExA", &win32_ret_val<4u, 1u>},
    {0x0051B220u, "USER32.dll!GetMenuState", &win32_ret_val<12u, 0u>},
    {0x0051B224u, "USER32.dll!GetSubMenu", &win32_ret_val<8u, kHMENU_MAIN>},
    {0x0051B228u, "USER32.dll!GetKeyState", &u32_get_key_state},
    {0x0051B22Cu, "USER32.dll!DestroyWindow", &u32_destroy_window},
    {0x0051B230u, "USER32.dll!GetLastActivePopup", &win32_ret_val<4u, kHWND_MAIN>},
    {0x0051B234u, "USER32.dll!GetSystemMetrics", &u32_get_system_metrics},
    {0x0051B238u, "USER32.dll!PeekMessageA", &u32_peek_message_a},
    {0x0051B23Cu, "USER32.dll!ShowWindow", &win32_ret_val<8u, 1u>},
    {0x0051B240u, "USER32.dll!wsprintfA", &u32_wsprintf_a_cdecl},
    {0x0051B244u, "USER32.dll!PostThreadMessageA", &u32_post_thread_message_a},
    {0x0051B248u, "USER32.dll!GetCursorPos", [](CpuContext& c, GuestMemory& m){ uint32_t p=c.arg32(m,0); if(p){m.w32(p,0);m.w32(p+4,0);} c.eax=1; c.ret_stdcall(m,4); }},
    {0x0051B24Cu, "USER32.dll!ScreenToClient", &win32_ret_val<8u, 1u>},
    {0x0051B250u, "USER32.dll!GetClientRect", &u32_get_client_rect},
    {0x0051B254u, "USER32.dll!SendMessageA", &win32_ret_val<16u, 0u>},
    {0x0051B258u, "USER32.dll!AdjustWindowRect", &u32_adjust_window_rect},
    {0x0051B25Cu, "USER32.dll!CreateDialogParamA", &win32_ret_val<20u, kHWND_MAIN>},
    {0x0051B260u, "USER32.dll!GetWindowRect", &u32_get_client_rect},
    {0x0051B264u, "USER32.dll!CheckMenuItem", &win32_ret_val<12u, 0u>},
    {0x0051B268u, "USER32.dll!SetWindowLongA", [](CpuContext& c, GuestMemory& m){ uint32_t idx=c.arg32(m,1), v=c.arg32(m,2); std::lock_guard<std::mutex> lk(g_w32.state_mtx); uint32_t prev=g_w32.window_longs[idx]; g_w32.window_longs[idx]=v; c.eax=prev; c.ret_stdcall(m,12); }},
    {0x0051B26Cu, "USER32.dll!GetParent", &win32_ret_val<4u, 0u>},
    {0x0051B270u, "USER32.dll!MoveWindow", &win32_ret_val<24u, 1u>},
    {0x0051B274u, "USER32.dll!DialogBoxParamA", &u32_dialog_box_param_a},
    {0x0051B278u, "USER32.dll!MessageBoxA", &u32_message_box_a},
    {0x0051B27Cu, "USER32.dll!EmptyClipboard", &win32_ret_val<0u, 1u>},
    {0x0051B280u, "USER32.dll!SetClipboardData", &win32_ret_val<8u, 0u>},
    {0x0051B284u, "USER32.dll!GetClipboardData", &win32_ret_val<4u, 0u>},
    {0x0051B288u, "USER32.dll!CloseClipboard", &win32_ret_val<0u, 1u>},
    {0x0051B28Cu, "USER32.dll!OpenClipboard", &win32_ret_val<4u, 1u>},
    {0x0051B290u, "USER32.dll!ReleaseDC", &win32_ret_val<8u, 1u>},
    {0x0051B294u, "USER32.dll!SetWindowTextA", &win32_ret_val<8u, 1u>},
    {0x0051B298u, "USER32.dll!SetForegroundWindow", &win32_ret_val<4u, 1u>},
    {0x0051B29Cu, "USER32.dll!TranslateMessage", &win32_ret_val<4u, 1u>},
    {0x0051B2A0u, "USER32.dll!PostQuitMessage", &u32_post_quit_message},
    {0x0051B2A4u, "USER32.dll!DefWindowProcA", &win32_ret_val<16u, 0u>},
    {0x0051B2A8u, "USER32.dll!ShowCursor", &u32_show_cursor},
    {0x0051B2ACu, "USER32.dll!UpdateWindow", &win32_ret_val<4u, 1u>},
    {0x0051B2B0u, "USER32.dll!IsWindowVisible", &win32_ret_val<4u, 1u>},
    {0x0051B2B4u, "USER32.dll!IsWindowEnabled", &win32_ret_val<4u, 1u>},
    {0x0051B2B8u, "USER32.dll!GetDC", &win32_ret_val<4u, kHDC_MAIN>},
    {0x0051B2BCu, "USER32.dll!GetActiveWindow", &win32_ret_val<0u, kHWND_MAIN>},
    {0x0051B2C0u, "USER32.dll!DestroyMenu", &win32_ret_val<4u, 1u>},
    {0x0051B2C4u, "USER32.dll!FindWindowA", &win32_ret_val<8u, 0u>},
    {0x0051B2C8u, "USER32.dll!SetWindowPos", &win32_ret_val<28u, 1u>},
    {0x0051B2CCu, "USER32.dll!LoadMenuA", &win32_ret_val<8u, kHMENU_MAIN>},
    {0x0051B2D0u, "USER32.dll!CheckDlgButton", &win32_ret_val<12u, 1u>},
    {0x0051B2D4u, "USER32.dll!SetDlgItemTextA", &win32_ret_val<12u, 1u>},
    {0x0051B2D8u, "USER32.dll!CheckRadioButton", &win32_ret_val<16u, 1u>},
    {0x0051B2DCu, "USER32.dll!GetWindowLongA", [](CpuContext& c, GuestMemory& m){ uint32_t idx=c.arg32(m,1); std::lock_guard<std::mutex> lk(g_w32.state_mtx); c.eax=g_w32.window_longs[idx]; c.ret_stdcall(m,8); }},
    {0x0051B2E0u, "USER32.dll!LoadIconA", &win32_ret_val<8u, 0x10000020u>},
    {0x0051B2E4u, "USER32.dll!DispatchMessageA", &win32_ret_val<4u, 0u>},
    {0x0051B2E8u, "USER32.dll!LoadCursorA", &win32_ret_val<8u, 0x10000021u>},
    {0x0051B2ECu, "USER32.dll!BeginPaint", &win32_ret_val<8u, kHDC_MAIN>},
    {0x0051B2F0u, "USER32.dll!SendDlgItemMessageA", &win32_ret_val<20u, 0u>},
    {0x0051B2F4u, "USER32.dll!GetDlgItem", &win32_ret_val<8u, kHWND_MAIN>},
    {0x0051B2F8u, "USER32.dll!SetFocus", &win32_ret_val<4u, kHWND_MAIN>},
    {0x0051B2FCu, "USER32.dll!GetDlgCtrlID", &win32_ret_val<4u, 0u>},
    {0x0051B300u, "USER32.dll!IsDlgButtonChecked", &win32_ret_val<8u, 0u>},
    {0x0051B304u, "USER32.dll!EnableWindow", &win32_ret_val<8u, 1u>},
    {0x0051B308u, "USER32.dll!EndPaint", &win32_ret_val<8u, 1u>},
    {0x0051B30Cu, "USER32.dll!CreateWindowExA", &win32_ret_val<48u, kHWND_MAIN>},
    {0x0051B310u, "USER32.dll!SetRect", &u32_set_rect},
    {0x0051B314u, "USER32.dll!SetTimer", &win32_ret_val<16u, 1u>},
    {0x0051B318u, "USER32.dll!KillTimer", &win32_ret_val<8u, 1u>},
    {0x0051B31Cu, "USER32.dll!EndDialog", &win32_ret_val<8u, 1u>},
    {0x0051B320u, "USER32.dll!GetDlgItemTextA", [](CpuContext& c, GuestMemory& m){ uint32_t b=c.arg32(m,2), sz=c.arg32(m,3); if(b&&sz) m.w8(b,0); c.eax=0; c.ret_stdcall(m,16); }},
    {0x0051B324u, "USER32.dll!MapWindowPoints", &win32_ret_val<16u, 0u>},
    {0x0051B328u, "USER32.dll!ClientToScreen", &win32_ret_val<8u, 1u>},
    {0x0051B330u, "WINMM.dll!timeBeginPeriod", &win32_ret_val<4u, 0u>},
    {0x0051B334u, "WINMM.dll!timeGetTime", &k32_get_tick_count},
    {0x0051B33Cu, "WS2_32.dll!send", &ws2_send},
    {0x0051B340u, "WS2_32.dll!htons", &ws2_htons_ntohs},
    {0x0051B344u, "WS2_32.dll!listen", &ws2_listen},
    {0x0051B348u, "WS2_32.dll!bind", &ws2_bind},
    {0x0051B34Cu, "WS2_32.dll!recv", &ws2_recv},
    {0x0051B350u, "WS2_32.dll!accept", &ws2_accept},
    {0x0051B354u, "WS2_32.dll!gethostbyname", &ws2_gethostbyname},
    {0x0051B358u, "WS2_32.dll!inet_addr", &ws2_inet_addr},
    {0x0051B35Cu, "WS2_32.dll!closesocket", &ws2_closesocket},
    {0x0051B360u, "WS2_32.dll!WSAGetLastError", &ws2_get_last_error},
    {0x0051B364u, "WS2_32.dll!gethostbyaddr", &win32_ret_val<12u, 0u>},
    {0x0051B368u, "WS2_32.dll!WSAAsyncSelect", &ws2_wsa_async_select},
    {0x0051B36Cu, "WS2_32.dll!WSARecv", &ws2_wsa_recv},
    {0x0051B370u, "WS2_32.dll!ntohs", &ws2_htons_ntohs},
    {0x0051B374u, "WS2_32.dll!sendto", &ws2_sendto},
    {0x0051B378u, "WS2_32.dll!recvfrom", &ws2_recvfrom},
    {0x0051B37Cu, "WS2_32.dll!inet_ntoa", &ws2_inet_ntoa},
    {0x0051B380u, "WS2_32.dll!WSAStartup", &win32_ret_val<8u, 0u>},
    {0x0051B384u, "WS2_32.dll!WSACleanup", &win32_ret_val<0u, 0u>},
    {0x0051B388u, "WS2_32.dll!shutdown", &ws2_shutdown},
    {0x0051B38Cu, "WS2_32.dll!socket", &ws2_socket},
    {0x0051B390u, "WS2_32.dll!connect", &ws2_connect},
    {0x0051B398u, "d3d9.dll!Direct3DCreate9", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B398u,"Direct3DCreate9"); }},
    {0x0051B3A0u, "d3dx9_36.dll!D3DXMatrixRotationX", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3A0u,"D3DXMatrixRotationX"); }},
    {0x0051B3A4u, "d3dx9_36.dll!D3DXMatrixScaling", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3A4u,"D3DXMatrixScaling"); }},
    {0x0051B3A8u, "d3dx9_36.dll!D3DXMatrixRotationY", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3A8u,"D3DXMatrixRotationY"); }},
    {0x0051B3ACu, "d3dx9_36.dll!D3DXMatrixMultiply", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3ACu,"D3DXMatrixMultiply"); }},
    {0x0051B3B0u, "d3dx9_36.dll!D3DXMatrixTranslation", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3B0u,"D3DXMatrixTranslation"); }},
    {0x0051B3B4u, "d3dx9_36.dll!D3DXSaveSurfaceToFileA", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3B4u,"D3DXSaveSurfaceToFileA"); }},
    {0x0051B3B8u, "d3dx9_36.dll!D3DXVec3Transform", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3B8u,"D3DXVec3Transform"); }},
    {0x0051B3BCu, "d3dx9_36.dll!D3DXVec3TransformCoord", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3BCu,"D3DXVec3TransformCoord"); }},
    {0x0051B3C0u, "d3dx9_36.dll!D3DXVec3TransformCoordArray", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3C0u,"D3DXVec3TransformCoordArray"); }},
    {0x0051B3C4u, "d3dx9_36.dll!D3DXMatrixLookAtLH", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3C4u,"D3DXMatrixLookAtLH"); }},
    {0x0051B3C8u, "d3dx9_36.dll!D3DXMatrixPerspectiveFovLH", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3C8u,"D3DXMatrixPerspectiveFovLH"); }},
    {0x0051B3CCu, "d3dx9_36.dll!D3DXVec3Normalize", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3CCu,"D3DXVec3Normalize"); }},
    {0x0051B3D0u, "d3dx9_36.dll!D3DXLoadSurfaceFromSurface", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3D0u,"D3DXLoadSurfaceFromSurface"); }},
    {0x0051B3D4u, "d3dx9_36.dll!D3DXCreateFontA", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3D4u,"D3DXCreateFontA"); }},
    {0x0051B3D8u, "d3dx9_36.dll!D3DXFillTexture", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3D8u,"D3DXFillTexture"); }},
    {0x0051B3DCu, "d3dx9_36.dll!D3DXMatrixRotationYawPitchRoll", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3DCu,"D3DXMatrixRotationYawPitchRoll"); }},
    {0x0051B3E0u, "d3dx9_36.dll!D3DXCreateEffect", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3E0u,"D3DXCreateEffect"); }},
    {0x0051B3E4u, "d3dx9_36.dll!D3DXCreateTextureFromFileInMemoryEx", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3E4u,"D3DXCreateTextureFromFileInMemoryEx"); }},
    {0x0051B3E8u, "d3dx9_36.dll!D3DXGetImageInfoFromFileInMemory", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3E8u,"D3DXGetImageInfoFromFileInMemory"); }},
    {0x0051B3ECu, "d3dx9_36.dll!D3DXVec3TransformArray", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3ECu,"D3DXVec3TransformArray"); }},
    {0x0051B3F0u, "d3dx9_36.dll!D3DXMatrixRotationZ", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3F0u,"D3DXMatrixRotationZ"); }},
    {0x0051B3F4u, "d3dx9_36.dll!D3DXCreateTexture", [](CpuContext& c, GuestMemory& m){ d3d_iat_forward(c,m,0x0051B3F4u,"D3DXCreateTexture"); }},
    {0x0051B3FCu, "ole32.dll!CoTaskMemFree", [](CpuContext& c, GuestMemory& m){ m.guest_free(c.arg32(m,0)); c.ret_stdcall(m,4); }},
    {0x0051B400u, "ole32.dll!CoCreateInstance", &ole32_co_create_instance},
    {0x0051B404u, "ole32.dll!CoUninitialize", &win32_ret_void<0u>},
    {0x0051B408u, "ole32.dll!CoInitializeEx", &win32_ret_val<8u, 0u>},
};

const IatDescriptor* lookup_iat_desc(uint32_t iat_va) noexcept {
    constexpr size_t count = sizeof(kIatTable) / sizeof(kIatTable[0]);
    const auto* begin = kIatTable;
    const auto* end   = kIatTable + count;
    const auto* it = std::lower_bound(begin, end, iat_va,
        [](const IatDescriptor& d, uint32_t v) { return d.va < v; });
    if (it != end && it->va == iat_va) {
        return it;
    }
    return nullptr;
}

} // namespace

void hle_win32_init(const std::string& assets_dir, uint32_t screen_width, uint32_t screen_height) {
    hle_win32_shutdown();
    {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        g_w32.assets_dir     = assets_dir;
        g_w32.screen_w       = (screen_width > 0u) ? screen_width : 640u;
        g_w32.screen_h       = (screen_height > 0u) ? screen_height : 480u;
        g_w32.boot_time      = std::chrono::steady_clock::now();
        g_w32.main_thread_id = std::this_thread::get_id();
        g_w32.quit_requested.store(false, std::memory_order_release);
        g_w32.quit_code.store(0, std::memory_order_relaxed);
        g_w32.hostent_va     = 0u;
        g_w32.env_ansi_va    = 0u;
        g_w32.env_wide_va    = 0u;
        g_w32.cmdline_va     = 0u;
        g_w32.temp_str_va    = 0u;
        g_w32.window_longs[static_cast<uint32_t>(-6)] = kHINST_MAIN; // GWL_HINSTANCE
        tls_tid              = 1u;
        tls_is_worker        = false;
        tls_pending_apcs.clear();
    }
    {
        std::lock_guard<std::mutex> llock(g_log.mtx);
        if (g_log.fp != nullptr) {
            std::fclose(g_log.fp);
            g_log.fp = nullptr;
        }
        g_log.ring.clear();
        g_log.lines_written = 0u;
        g_log.missing_file_logs.store(0u, std::memory_order_relaxed);
        g_log.found_file_logs.store(0u, std::memory_order_relaxed);
        g_log.thread_spawn_count.store(0u, std::memory_order_relaxed);
        g_log.thread_fail_count.store(0u, std::memory_order_relaxed);
        g_log.destroy_window_calls.store(0u, std::memory_order_relaxed);
        g_log.dialog_box_calls.store(0u, std::memory_order_relaxed);
        g_log.cursor_display_count.store(0, std::memory_order_relaxed);
        if (!assets_dir.empty()) {
            const fs::path log_path = fs::path(assets_dir) / "mbaa_debug.log";
            g_log.fp = std::fopen(log_path.string().c_str(), "wb");
        }
    }
    hle_win32_log("Win32 HLE init assets_dir=%s (%ux%u)",
                  assets_dir.c_str(), g_w32.screen_w, g_w32.screen_h);
}

void hle_win32_shutdown() {
    g_w32.quit_requested.store(true, std::memory_order_release);
    wake_all_sync_waiters();
    {
        std::unique_lock<std::mutex> wlk(g_w32.worker_mtx);
        g_w32.worker_cv.wait_for(wlk, std::chrono::milliseconds(400), []() {
            return g_w32.active_workers <= 0;
        });
    }
    tls_pending_apcs.clear();

    std::unordered_map<uint32_t, HandleRecord> leftover;
    {
        std::lock_guard<std::mutex> lock(g_w32.state_mtx);
        leftover.swap(g_w32.handles);
        g_w32.named_mutexes.clear();
        g_w32.crit_sections.clear();
        g_w32.thread_queues.clear();
        g_w32.window_longs.clear();
        g_w32.selected_font_by_dc.clear();
        g_w32.frame_yield_cb = nullptr;
    }
    for (auto& kv : leftover) {
        if (kv.second.kind == HandleKind::File && kv.second.file && kv.second.file->fp) {
            std::fclose(kv.second.file->fp);
            kv.second.file->fp = nullptr;
        }
    }
    {
        std::lock_guard<std::mutex> llock(g_log.mtx);
        if (g_log.fp != nullptr) {
            std::fclose(g_log.fp);
            g_log.fp = nullptr;
        }
    }
}

uint32_t hle_thunk_to_iat_va(uint32_t va) noexcept {
    constexpr uint32_t span = GuestMemory::kIatRangeEnd - GuestMemory::kIatRangeStart;
    if (va >= GuestMemory::kIatThunkBase && va < GuestMemory::kIatThunkBase + span) {
        return GuestMemory::kIatRangeStart + (va - GuestMemory::kIatThunkBase);
    }
    return 0u;
}

const char* hle_iat_name(uint32_t va) {
    const uint32_t resolved = (hle_thunk_to_iat_va(va) != 0u) ? hle_thunk_to_iat_va(va) : va;
    if (const auto* d = lookup_iat_desc(resolved)) {
        return d->name;
    }
    return nullptr;
}

void hle_iat_call(CpuContext& ctx, GuestMemory& mem, uint32_t iat_va) {
    const uint32_t resolved = (hle_thunk_to_iat_va(iat_va) != 0u) ? hle_thunk_to_iat_va(iat_va) : iat_va;
    if (const auto* d = lookup_iat_desc(resolved)) {
        d->fn(ctx, mem);
        return;
    }
    std::fprintf(stderr, "[hle_win32] Unhandled IAT VA 0x%08x\n", resolved);
    ctx.eax = 0u;
    ctx.ret_cdecl(mem);
}

void hle_win32_set_guest_main_thread() {
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    g_w32.main_thread_id = std::this_thread::get_id();
    tls_tid = 1u;
    tls_is_worker = false;
    tls_pending_apcs.clear();
}

void hle_win32_set_frame_yield_callback(std::function<bool()> callback) {
    std::lock_guard<std::mutex> lock(g_w32.state_mtx);
    g_w32.frame_yield_cb = std::move(callback);
}

std::string hle_win32_resolve_path(const std::string& guest_path, bool for_write) {
    return resolve_asset_path(guest_path, for_write, nullptr).string();
}

void hle_win32_post_quit(int exit_code) {
    g_w32.quit_code.store(exit_code, std::memory_order_relaxed);
    g_w32.quit_requested.store(true, std::memory_order_release);
    wake_all_sync_waiters();
}

bool hle_win32_is_quit_requested() noexcept {
    return g_w32.quit_requested.load(std::memory_order_acquire);
}

void hle_win32_signal_event(uint32_t handle_val) {
    HandleRecord rec;
    if (get_handle(handle_val, rec) && rec.kind == HandleKind::Event && rec.event) {
        std::lock_guard<std::mutex> lock(rec.event->mtx);
        rec.event->signaled = true;
        rec.event->cv.notify_all();
    }
}

void hle_win32_log(const char* fmt, ...) {
    if (!fmt) return;
    char buf[1024] = {};
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    append_debug_log_line(buf);
}

std::string hle_win32_recent_logs(size_t max_lines) {
    std::lock_guard<std::mutex> llock(g_log.mtx);
    std::string out;
    const size_t total = g_log.ring.size();
    const size_t start = (max_lines < total) ? (total - max_lines) : 0u;
    for (size_t i = start; i < total; ++i) {
        if (!out.empty()) out.push_back('\n');
        out += g_log.ring[i];
    }
    out += "\nthrSpawn=" + std::to_string(g_log.thread_spawn_count.load(std::memory_order_relaxed)) +
           " thrFail=" + std::to_string(g_log.thread_fail_count.load(std::memory_order_relaxed)) +
           " missFiles=" + std::to_string(g_log.missing_file_logs.load(std::memory_order_relaxed)) +
           " destroyWin=" + std::to_string(g_log.destroy_window_calls.load(std::memory_order_relaxed));
    return out;
}

} // namespace mbaa_recomp
