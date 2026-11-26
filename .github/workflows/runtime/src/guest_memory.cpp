#include "mbaa_recomp/guest_memory.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iterator>

#if defined(__APPLE__) || defined(__unix__)
#include <sys/mman.h>
#include <unistd.h>
#elif defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace mbaa_recomp {

namespace {

uint16_t read_le16_raw(const uint8_t* p) noexcept {
    return static_cast<uint16_t>(p[0]) | (static_cast<uint16_t>(p[1]) << 8);
}

uint32_t read_le32_raw(const uint8_t* p) noexcept {
    return static_cast<uint32_t>(p[0]) |
           (static_cast<uint32_t>(p[1]) << 8) |
           (static_cast<uint32_t>(p[2]) << 16) |
           (static_cast<uint32_t>(p[3]) << 24);
}

uint64_t align_up_u64(uint64_t val, uint64_t align) noexcept {
    if (align <= 1u) return val;
    return (val + (align - 1u)) & ~(align - 1u);
}

uint32_t normalize_align(uint32_t align, uint32_t min_align) noexcept {
    const uint32_t a = std::max(align, min_align);
    if ((a & (a - 1u)) == 0u) return a;
    uint32_t p = min_align;
    while (p < a && p < 0x80000000u) p <<= 1u;
    return p;
}

} // namespace

GuestMemory::GuestMemory() = default;

GuestMemory::~GuestMemory() {
    shutdown();
}

bool GuestMemory::init() {
    shutdown();

#if defined(__APPLE__) || defined(__unix__)
    const long ps = ::sysconf(_SC_PAGESIZE);
    host_page_size_ = (ps >= 4096 && (ps & (ps - 1)) == 0) ? static_cast<uint32_t>(ps) : 16384u;
    void* mapped = ::mmap(nullptr, kArenaSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
    if (mapped == MAP_FAILED || mapped == nullptr) {
        last_error_ = "mmap failed to reserve 256 MiB guest arena";
        return false;
    }
    uint8_t* new_base = static_cast<uint8_t*>(mapped);
    const bool new_mmap = true;
#elif defined(_WIN32)
    host_page_size_ = 4096u;
    void* mapped = ::VirtualAlloc(nullptr, kArenaSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (mapped == nullptr) {
        last_error_ = "VirtualAlloc failed to reserve 256 MiB guest arena";
        return false;
    }
    uint8_t* new_base = static_cast<uint8_t*>(mapped);
    const bool new_mmap = true;
#else
    host_page_size_ = 4096u;
    uint8_t* new_base = static_cast<uint8_t*>(std::calloc(1, kArenaSize));
    if (new_base == nullptr) {
        last_error_ = "calloc failed for 256 MiB guest arena";
        return false;
    }
    const bool new_mmap = false;
#endif

    {
        std::lock_guard<std::mutex> lock(alloc_mutex_);
        base_                     = new_base;
        using_mmap_               = new_mmap;
        heap_cursor_              = kHeapBase;
        thunk_cursor_             = kThunkPageBase;
        heap_used_bytes_          = 0u;
        active_thread_stack_mask_ = 0u;
        active_allocs_.clear();
        free_blocks_.clear();
        free_by_size_.clear();
        active_overflow_stacks_.clear();
    }
    sections_.clear();
    last_error_.clear();

    init_synthetic_teb_peb();
    return true;
}

void GuestMemory::shutdown() {
    uint8_t* old_base = nullptr;
    bool old_mmap = false;
    {
        std::lock_guard<std::mutex> lock(alloc_mutex_);
        old_base                  = base_;
        old_mmap                  = using_mmap_;
        base_                     = nullptr;
        using_mmap_               = false;
        heap_cursor_              = kHeapBase;
        thunk_cursor_             = kThunkPageBase;
        heap_used_bytes_          = 0u;
        active_thread_stack_mask_ = 0u;
        active_allocs_.clear();
        free_blocks_.clear();
        free_by_size_.clear();
        active_overflow_stacks_.clear();
    }
    sections_.clear();

    if (old_base != nullptr) {
#if defined(__APPLE__) || defined(__unix__)
        if (old_mmap) {
            ::munmap(old_base, kArenaSize);
        } else {
            std::free(old_base);
        }
#elif defined(_WIN32)
        if (old_mmap) {
            ::VirtualFree(old_base, 0, MEM_RELEASE);
        } else {
            std::free(old_base);
        }
#else
        std::free(old_base);
#endif
    }
}

void GuestMemory::init_synthetic_teb_peb() {
    // Win32 NT_TIB / TEB at fs:[0] = kTebBase
    w32(kTebBase + 0x00u, 0xFFFFFFFFu); // ExceptionList sentinel
    w32(kTebBase + 0x04u, kStackTop);   // StackBase
    w32(kTebBase + 0x08u, kStackBase);  // StackLimit
    w32(kTebBase + 0x18u, kTebBase);    // Self pointer (NtTib.Self)
    w32(kTebBase + 0x20u, 0x00001000u); // ClientId.UniqueProcess
    w32(kTebBase + 0x24u, 0x00001001u); // ClientId.UniqueThread
    w32(kTebBase + 0x2Cu, kTebBase + 0x1000u); // ThreadLocalStoragePointer
    w32(kTebBase + 0x30u, kPebBase);    // ProcessEnvironmentBlock

    // Win32 PEB at kPebBase
    w8(kPebBase + 0x02u, 0u);           // BeingDebugged = FALSE
    w32(kPebBase + 0x08u, kImageBase);  // ImageBaseAddress
    w32(kPebBase + 0x18u, kHeapBase);   // ProcessHeap
    w32(kPebBase + 0x68u, 1u);          // NumberOfProcessors
    w32(kPebBase + 0xA4u, 6u);          // OSMajorVersion = 6
    w32(kPebBase + 0xA8u, 1u);          // OSMinorVersion = 1 (Windows 7)
    w16(kPebBase + 0xACu, 7601u);       // OSBuildNumber
    w32(kPebBase + 0xB0u, 2u);          // OSPlatformId = VER_PLATFORM_WIN32_NT
}

bool GuestMemory::load_pe_sections(const std::string& exe_path) {
    if (base_ == nullptr && !init()) {
        return false;
    }

    std::ifstream ifs(exe_path, std::ios::binary | std::ios::ate);
    if (!ifs.is_open()) {
        last_error_ = "Failed to open BYOC PE binary: " + exe_path;
        return false;
    }

    const std::streamsize file_size_s = ifs.tellg();
    if (file_size_s < 0x100) {
        last_error_ = "PE file too small: " + exe_path;
        return false;
    }
    const size_t file_size = static_cast<size_t>(file_size_s);
    std::vector<uint8_t> raw(file_size);
    ifs.seekg(0, std::ios::beg);
    if (!ifs.read(reinterpret_cast<char*>(raw.data()), file_size_s)) {
        last_error_ = "Failed to read PE file bytes: " + exe_path;
        return false;
    }

    if (read_le16_raw(raw.data()) != 0x5A4Du) { // 'MZ'
        last_error_ = "Invalid MZ DOS header in " + exe_path;
        return false;
    }
    const uint32_t pe_off = read_le32_raw(raw.data() + 0x3Cu);
    if (pe_off + 24u + 96u > file_size ||
        raw[pe_off] != 'P' || raw[pe_off + 1] != 'E' || raw[pe_off + 2] != 0 || raw[pe_off + 3] != 0) {
        last_error_ = "Invalid PE header offset/signature in " + exe_path;
        return false;
    }

    const uint8_t* coff = raw.data() + pe_off + 4u;
    const uint16_t machine       = read_le16_raw(coff + 0u);
    const uint16_t num_sections  = read_le16_raw(coff + 2u);
    const uint16_t opt_hdr_size  = read_le16_raw(coff + 16u);
    if (machine != 0x014Cu) {
        last_error_ = "Expected x86-32 PE (machine 0x014C)";
        return false;
    }

    const uint8_t* opt = coff + 20u;
    if (opt_hdr_size < 96u || pe_off + 24u + opt_hdr_size > file_size || read_le16_raw(opt) != 0x010Bu) {
        last_error_ = "Invalid PE32 optional header";
        return false;
    }

    const uint32_t image_base      = read_le32_raw(opt + 28u);
    const uint32_t size_of_headers = read_le32_raw(opt + 60u);
    const uint32_t load_base       = (image_base != 0) ? image_base : kImageBase;

    const size_t hdr_copy = std::min<size_t>(size_of_headers, file_size);
    if (!write_bytes(load_base, raw.data(), hdr_copy)) {
        last_error_ = "Failed writing PE headers into guest arena";
        return false;
    }

    sections_.clear();
    const size_t sec_table_off = pe_off + 24u + opt_hdr_size;
    for (uint16_t i = 0; i < num_sections; ++i) {
        const size_t sh_off = sec_table_off + static_cast<size_t>(i) * 40u;
        if (sh_off + 40u > file_size) break;
        const uint8_t* sh = raw.data() + sh_off;

        char name_buf[9] = {};
        std::memcpy(name_buf, sh, 8);
        const uint32_t virt_size = read_le32_raw(sh + 8u);
        const uint32_t virt_addr = read_le32_raw(sh + 12u);
        const uint32_t raw_size  = read_le32_raw(sh + 16u);
        const uint32_t raw_ptr   = read_le32_raw(sh + 20u);

        const uint32_t sec_va   = load_base + virt_addr;
        const uint32_t span_sz  = std::max(virt_size, raw_size);
        if (!in_bounds(sec_va, span_sz)) {
            last_error_ = std::string("Section out of guest arena bounds: ") + name_buf;
            return false;
        }

        zero_bytes(sec_va, span_sz);
        if (raw_size > 0 && raw_ptr < file_size) {
            const size_t copy_len = std::min<size_t>(raw_size, file_size - raw_ptr);
            write_bytes(sec_va, raw.data() + raw_ptr, copy_len);
        }

        PeSectionInfo info;
        info.name = name_buf;
        info.va = sec_va;
        info.virtual_size = virt_size;
        info.raw_size = raw_size;
        sections_.push_back(std::move(info));
    }

    patch_iat_thunks();
    return true;
}

void GuestMemory::patch_iat_thunks() {
    // Walk PE DataDirectory[1] (Import Table) so every IAT slot in 0x0051B000..0x0051B40C
    // holds a deterministic synthetic VA inside kIatThunkBase.
    // This makes register-indirect calls (`mov edi, [0x51B238]; call edi`) work seamlessly.
    const uint32_t pe_off = r32(kImageBase + 0x3Cu);
    if (pe_off == 0 || pe_off > 0x1000u) return;

    const uint32_t opt_va = kImageBase + pe_off + 24u;
    const uint32_t num_dirs = r32(opt_va + 92u);
    if (num_dirs <= 1) return;

    const uint32_t imp_rva = r32(opt_va + 96u + 8u); // DataDirectory[1].VirtualAddress
    if (imp_rva == 0) return;

    uint32_t desc_va = kImageBase + imp_rva;
    for (int d = 0; d < 256; ++d) {
        const uint32_t orig_first_thunk = r32(desc_va + 0u);
        const uint32_t name_rva         = r32(desc_va + 12u);
        const uint32_t first_thunk      = r32(desc_va + 16u);
        if (orig_first_thunk == 0 && name_rva == 0 && first_thunk == 0) {
            break;
        }
        if (first_thunk != 0) {
            uint32_t iat_va = kImageBase + first_thunk;
            for (int f = 0; f < 4096; ++f) {
                const uint32_t cur = r32(iat_va);
                if (cur == 0) break;
                if (iat_va >= kIatRangeStart && iat_va < kIatRangeEnd) {
                    const uint32_t synth_va = kIatThunkBase + (iat_va - kIatRangeStart);
                    w32(iat_va, synth_va);
                }
                iat_va += 4u;
            }
        }
        desc_va += 20u;
    }
}

uint8_t GuestMemory::r8(uint32_t va) const noexcept {
    if (!in_bounds(va, 1)) return 0;
    return base_[va];
}

uint16_t GuestMemory::r16(uint32_t va) const noexcept {
    if (!in_bounds(va, 2)) return 0;
    uint16_t v = 0;
    std::memcpy(&v, base_ + va, sizeof(v));
    return v;
}

uint32_t GuestMemory::r32(uint32_t va) const noexcept {
    if (!in_bounds(va, 4)) return 0;
    uint32_t v = 0;
    std::memcpy(&v, base_ + va, sizeof(v));
    return v;
}

uint64_t GuestMemory::r64(uint32_t va) const noexcept {
    if (!in_bounds(va, 8)) return 0;
    uint64_t v = 0;
    std::memcpy(&v, base_ + va, sizeof(v));
    return v;
}

float GuestMemory::rf32(uint32_t va) const noexcept {
    if (!in_bounds(va, 4)) return 0.0f;
    float v = 0.0f;
    std::memcpy(&v, base_ + va, sizeof(v));
    return v;
}

double GuestMemory::rf64(uint32_t va) const noexcept {
    if (!in_bounds(va, 8)) return 0.0;
    double v = 0.0;
    std::memcpy(&v, base_ + va, sizeof(v));
    return v;
}

void GuestMemory::w8(uint32_t va, uint8_t v) noexcept {
    if (!in_bounds(va, 1)) return;
    base_[va] = v;
}

void GuestMemory::w16(uint32_t va, uint16_t v) noexcept {
    if (!in_bounds(va, 2)) return;
    std::memcpy(base_ + va, &v, sizeof(v));
}

void GuestMemory::w32(uint32_t va, uint32_t v) noexcept {
    if (!in_bounds(va, 4)) return;
    std::memcpy(base_ + va, &v, sizeof(v));
}

void GuestMemory::w64(uint32_t va, uint64_t v) noexcept {
    if (!in_bounds(va, 8)) return;
    std::memcpy(base_ + va, &v, sizeof(v));
}

void GuestMemory::wf32(uint32_t va, float v) noexcept {
    if (!in_bounds(va, 4)) return;
    std::memcpy(base_ + va, &v, sizeof(v));
}

void GuestMemory::wf64(uint32_t va, double v) noexcept {
    if (!in_bounds(va, 8)) return;
    std::memcpy(base_ + va, &v, sizeof(v));
}

uint8_t* GuestMemory::ptr(uint32_t va) noexcept {
    if (!in_bounds(va, 1)) return nullptr;
    return base_ + va;
}

const uint8_t* GuestMemory::ptr(uint32_t va) const noexcept {
    if (!in_bounds(va, 1)) return nullptr;
    return base_ + va;
}

bool GuestMemory::read_bytes(uint32_t va, void* dst, size_t size) const noexcept {
    if (size == 0) return true;
    if (dst == nullptr || !in_bounds(va, size)) return false;
    std::memcpy(dst, base_ + va, size);
    return true;
}

bool GuestMemory::write_bytes(uint32_t va, const void* src, size_t size) noexcept {
    if (size == 0) return true;
    if (src == nullptr || !in_bounds(va, size)) return false;
    std::memcpy(base_ + va, src, size);
    return true;
}

bool GuestMemory::zero_bytes(uint32_t va, size_t size) noexcept {
    if (size == 0) return true;
    if (!in_bounds(va, size)) return false;
    std::memset(base_ + va, 0, size);
    return true;
}

std::string GuestMemory::read_cstring(uint32_t va, size_t max_len) const {
    if (va == 0 || !in_bounds(va, 1)) return {};
    std::string out;
    const size_t limit = std::min(max_len, static_cast<size_t>(kArenaSize - va));
    out.reserve(std::min<size_t>(limit, 128));
    for (size_t i = 0; i < limit; ++i) {
        const char ch = static_cast<char>(base_[va + i]);
        if (ch == '\0') break;
        out.push_back(ch);
    }
    return out;
}

std::u16string GuestMemory::read_wstring_utf16(uint32_t va, size_t max_chars) const {
    if (va == 0 || !in_bounds(va, 2)) return {};
    std::u16string out;
    const size_t limit = std::min(max_chars, static_cast<size_t>((kArenaSize - va) / 2));
    for (size_t i = 0; i < limit; ++i) {
        const char16_t ch = static_cast<char16_t>(r16(va + static_cast<uint32_t>(i * 2)));
        if (ch == u'\0') break;
        out.push_back(ch);
    }
    return out;
}

uint32_t GuestMemory::write_cstring(uint32_t va, const std::string& s, size_t max_bytes) noexcept {
    if (va == 0 || !in_bounds(va, 1)) return 0;
    const size_t arena_avail = static_cast<size_t>(kArenaSize - va);
    const size_t cap = (max_bytes > 0) ? std::min(max_bytes, arena_avail) : arena_avail;
    if (cap == 0) return 0;
    const size_t copy_len = std::min(s.size(), cap - 1);
    if (copy_len > 0) {
        std::memcpy(base_ + va, s.data(), copy_len);
    }
    base_[va + copy_len] = 0;
    return static_cast<uint32_t>(copy_len);
}

void GuestMemory::insert_free_block_locked(uint32_t va, uint32_t size) {
    if (size == 0u) return;
    free_blocks_[va] = size;
    free_by_size_.emplace(size, va);
}

void GuestMemory::erase_free_block_locked(uint32_t va, uint32_t size) {
    free_blocks_.erase(va);
    free_by_size_.erase({size, va});
}

void GuestMemory::advise_reclaimable_locked(uint32_t va, uint32_t size, uint32_t min_bytes) noexcept {
#if defined(__APPLE__)
    if (!using_mmap_ || base_ == nullptr || size < min_bytes) return;
    const uint64_t ps = (host_page_size_ >= 4096u) ? static_cast<uint64_t>(host_page_size_) : 16384u;
    const uint64_t start = align_up_u64(va, ps);
    const uint64_t end   = (static_cast<uint64_t>(va) + size) & ~(ps - 1u);
    if (end > start && (end - start) >= min_bytes) {
        ::madvise(base_ + start, static_cast<size_t>(end - start), MADV_FREE);
    }
#else
    (void)va;
    (void)size;
    (void)min_bytes;
#endif
}

void GuestMemory::free_range_locked(uint32_t va, uint32_t size) {
    if (size == 0u) return;

    auto next_it = free_blocks_.lower_bound(va);

    // Coalesce with immediately preceding free block in O(log N)
    if (next_it != free_blocks_.begin()) {
        auto prev_it = std::prev(next_it);
        if (prev_it->first + prev_it->second == va) {
            const uint32_t prev_va = prev_it->first;
            const uint32_t prev_sz = prev_it->second;
            free_by_size_.erase({prev_sz, prev_va});
            free_blocks_.erase(prev_it);
            va = prev_va;
            size += prev_sz;
        }
    }

    // Coalesce with immediately following free block in O(log N)
    if (next_it != free_blocks_.end() && va + size == next_it->first) {
        const uint32_t next_va = next_it->first;
        const uint32_t next_sz = next_it->second;
        free_by_size_.erase({next_sz, next_va});
        free_blocks_.erase(next_it);
        size += next_sz;
    }

    // Rewind heap_cursor_ whenever the coalesced free region reaches the top of the heap
    if (va + size == heap_cursor_) {
        const uint32_t old_cursor = heap_cursor_;
        heap_cursor_ = va;
        advise_reclaimable_locked(heap_cursor_, old_cursor - heap_cursor_, 65536u);
        return;
    }

    insert_free_block_locked(va, size);
    advise_reclaimable_locked(va, size, 262144u);
}

uint32_t GuestMemory::guest_alloc_locked(uint32_t size, uint32_t align) {
    if (base_ == nullptr) return 0u;
    constexpr uint32_t kMaxHeapBytes = kLargeHeapLimit - kHeapBase;
    if (size > kMaxHeapBytes) return 0u;

    const uint32_t eff_align = normalize_align(align, kMinAllocAlign);
    if (eff_align > kMaxHeapBytes) return 0u;

    const uint64_t alloc_sz64 = align_up_u64(std::max<uint64_t>(size, kMinAllocAlign), kMinAllocAlign);
    if (alloc_sz64 > kMaxHeapBytes) return 0u;
    const uint32_t alloc_sz = static_cast<uint32_t>(alloc_sz64);

    // O(log N) best-fit (lowest-VA tie-break) search with alignment-aware leading/trailing splits
    for (auto sit = free_by_size_.lower_bound({alloc_sz, 0u}); sit != free_by_size_.end(); ++sit) {
        const uint32_t blk_sz  = sit->first;
        const uint32_t blk_va  = sit->second;
        const uint64_t blk_end = static_cast<uint64_t>(blk_va) + blk_sz;
        const uint64_t aligned = align_up_u64(blk_va, eff_align);
        if (aligned + alloc_sz <= blk_end) {
            const uint32_t va       = static_cast<uint32_t>(aligned);
            const uint32_t lead_sz  = va - blk_va;
            const uint32_t trail_va = va + alloc_sz;
            const uint32_t trail_sz = static_cast<uint32_t>(blk_end - trail_va);

            erase_free_block_locked(blk_va, blk_sz);
            if (lead_sz > 0u) {
                insert_free_block_locked(blk_va, lead_sz);
            }
            if (trail_sz > 0u) {
                insert_free_block_locked(trail_va, trail_sz);
            }
            active_allocs_[va] = alloc_sz;
            heap_used_bytes_ += alloc_sz;
            return va;
        }
    }

    // Bump-allocate from heap_cursor_, preserving any alignment padding gap in free_blocks_
    const uint64_t aligned64 = align_up_u64(heap_cursor_, eff_align);
    if (aligned64 + alloc_sz > kLargeHeapLimit) {
        return 0u;
    }
    const uint32_t va = static_cast<uint32_t>(aligned64);
    if (va > heap_cursor_) {
        insert_free_block_locked(heap_cursor_, va - heap_cursor_);
    }
    heap_cursor_ = va + alloc_sz;
    active_allocs_[va] = alloc_sz;
    heap_used_bytes_ += alloc_sz;
    return va;
}

void GuestMemory::guest_free_locked(uint32_t va) {
    if (va == 0u) return;
    auto it = active_allocs_.find(va);
    if (it == active_allocs_.end()) return;
    const uint32_t sz = it->second;
    active_allocs_.erase(it);
    heap_used_bytes_ -= sz;
    free_range_locked(va, sz);
}

uint32_t GuestMemory::guest_alloc(uint32_t size, uint32_t align) {
    std::lock_guard<std::mutex> lock(alloc_mutex_);
    return guest_alloc_locked(size, align);
}

uint32_t GuestMemory::guest_calloc(uint32_t count, uint32_t size) {
    constexpr uint64_t kMaxHeapBytes = static_cast<uint64_t>(kLargeHeapLimit - kHeapBase);
    const uint64_t total = static_cast<uint64_t>(count) * static_cast<uint64_t>(size);
    if (total > kMaxHeapBytes) return 0u;
    const uint32_t req = static_cast<uint32_t>(total);
    const uint32_t alloc_sz = static_cast<uint32_t>(
        align_up_u64(std::max<uint64_t>(req, kMinAllocAlign), kMinAllocAlign));
    const uint32_t va = guest_alloc(req, kMinAllocAlign);
    if (va != 0u) {
        zero_bytes(va, alloc_sz);
    }
    return va;
}

uint32_t GuestMemory::guest_realloc(uint32_t va, uint32_t new_size) {
    if (va == 0u) return guest_alloc(new_size, kMinAllocAlign);
    if (new_size == 0u) {
        guest_free(va);
        return 0u;
    }

    constexpr uint32_t kMaxHeapBytes = kLargeHeapLimit - kHeapBase;
    if (new_size > kMaxHeapBytes) return 0u;
    const uint64_t want_sz64 = align_up_u64(std::max<uint64_t>(new_size, kMinAllocAlign), kMinAllocAlign);
    if (want_sz64 > kMaxHeapBytes) return 0u;
    const uint32_t want_sz = static_cast<uint32_t>(want_sz64);

    std::lock_guard<std::mutex> lock(alloc_mutex_);
    if (base_ == nullptr) return 0u;

    auto it = active_allocs_.find(va);
    if (it == active_allocs_.end()) {
        return guest_alloc_locked(new_size, kMinAllocAlign);
    }

    const uint32_t old_sz = it->second;
    if (want_sz == old_sz) {
        return va;
    }

    // Shrink in-place and immediately return trailing bytes to the coalescing free pool
    if (want_sz < old_sz) {
        const uint32_t excess = old_sz - want_sz;
        it->second = want_sz;
        heap_used_bytes_ -= excess;
        free_range_locked(va + want_sz, excess);
        return va;
    }

    // Expand in-place if at top of heap or followed by a sufficiently large free block
    const uint32_t end_va     = va + old_sz;
    const uint32_t need_extra = want_sz - old_sz;
    if (end_va == heap_cursor_) {
        if (static_cast<uint64_t>(va) + want_sz <= kLargeHeapLimit) {
            heap_cursor_ = va + want_sz;
            it->second = want_sz;
            heap_used_bytes_ += need_extra;
            return va;
        }
    } else if (auto fit = free_blocks_.find(end_va); fit != free_blocks_.end() && fit->second >= need_extra) {
        const uint32_t next_sz = fit->second;
        erase_free_block_locked(end_va, next_sz);
        if (next_sz > need_extra) {
            insert_free_block_locked(end_va + need_extra, next_sz - need_extra);
        }
        it->second = want_sz;
        heap_used_bytes_ += need_extra;
        return va;
    }

    // Fallback: allocate new block, copy existing bytes, then release original block
    const uint32_t new_va = guest_alloc_locked(new_size, kMinAllocAlign);
    if (new_va == 0u) return 0u;
    std::memcpy(base_ + new_va, base_ + va, old_sz);
    active_allocs_.erase(va);
    heap_used_bytes_ -= old_sz;
    free_range_locked(va, old_sz);
    return new_va;
}

void GuestMemory::guest_free(uint32_t va) {
    if (va == 0u) return;
    std::lock_guard<std::mutex> lock(alloc_mutex_);
    guest_free_locked(va);
}

uint32_t GuestMemory::guest_msize(uint32_t va) const {
    if (va == 0u) return 0u;
    std::lock_guard<std::mutex> lock(alloc_mutex_);
    auto it = active_allocs_.find(va);
    return (it != active_allocs_.end()) ? it->second : 0u;
}

uint32_t GuestMemory::alloc_thunk_block(uint32_t size, uint32_t align) {
    if (size == 0u) return 0u;
    const uint32_t eff_align = normalize_align(align, 4u);
    std::lock_guard<std::mutex> lock(alloc_mutex_);
    if (base_ == nullptr) return 0u;
    const uint64_t aligned = align_up_u64(thunk_cursor_, eff_align);
    if (aligned + size > kComThunkBase) {
        return 0u;
    }
    const uint32_t va = static_cast<uint32_t>(aligned);
    thunk_cursor_ = va + size;
    std::memset(base_ + va, 0, size);
    return va;
}

uint32_t GuestMemory::alloc_thread_stack() {
    uint32_t stack_bottom = 0u;
    {
        std::lock_guard<std::mutex> lock(alloc_mutex_);
        if (base_ == nullptr) return 0u;

        // Pick the lowest free slot among the 16 fixed worker stacks to minimize dirty pages
        for (uint32_t slot = 0u; slot < kThreadStackSlotCount; ++slot) {
            const uint32_t bit = 1u << slot;
            if ((active_thread_stack_mask_ & bit) == 0u) {
                active_thread_stack_mask_ |= bit;
                stack_bottom = kThreadStackBase + slot * kThreadStackSize;
                break;
            }
        }

        // Overflow fallback when more than 16 worker threads are simultaneously alive
        if (stack_bottom == 0u) {
            stack_bottom = guest_alloc_locked(kThreadStackSize, kMinAllocAlign);
            if (stack_bottom == 0u) return 0u;
            active_overflow_stacks_.insert(stack_bottom);
        }
    }

    zero_bytes(stack_bottom, kThreadStackSize);
    return stack_bottom + kThreadStackSize - 0x100u;
}

void GuestMemory::free_thread_stack(uint32_t initial_esp) {
    if (initial_esp < kThreadStackSize - 0x100u || initial_esp >= kArenaSize) return;
    const uint32_t stack_bottom = initial_esp + 0x100u - kThreadStackSize;

    std::lock_guard<std::mutex> lock(alloc_mutex_);
    if (base_ == nullptr) return;

    if (stack_bottom >= kThreadStackBase &&
        stack_bottom < kThreadStackLimit &&
        ((stack_bottom - kThreadStackBase) % kThreadStackSize) == 0u) {
        const uint32_t slot = (stack_bottom - kThreadStackBase) / kThreadStackSize;
        const uint32_t bit = 1u << slot;
        if ((active_thread_stack_mask_ & bit) == 0u) {
            return; // Ignore double-free / unallocated slot
        }
        active_thread_stack_mask_ &= ~bit;
        return;
    }

    if (stack_bottom >= kHeapBase) {
        auto oit = active_overflow_stacks_.find(stack_bottom);
        if (oit == active_overflow_stacks_.end()) {
            return; // Ignore double-free or invalid ESP not owned as an overflow thread stack
        }
        active_overflow_stacks_.erase(oit);
        guest_free_locked(stack_bottom);
    }
}

uint32_t GuestMemory::heap_used_bytes() const noexcept {
    std::lock_guard<std::mutex> lock(alloc_mutex_);
    return heap_used_bytes_;
}

} // namespace mbaa_recomp
