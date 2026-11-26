#pragma once

/**
 * @file guest_memory.h
 * @brief Flat 32-bit guest virtual address space, PE section loader, and guest heap/thunk allocators.
 *
 * Address layout (within 256 MiB flat arena 0x00000000..0x0FFFFFFF):
 *   - 0x00300000..0x0030FFFF : Synthetic Win32 TEB/PEB/SEH sentinel page (fs:[0])
 *   - 0x00400000..0x007FFFFF : MBAA.exe PE image (.text, .rdata, .data, .rsrc, .new00)
 *   - 0x00800000..0x009FFFFF : 2 MiB primary guest thread stack
 *   - 0x00A00000..0x00DFFFFF : Secondary guest thread stacks (16 x 256 KiB each)
 *   - 0x00F00000..0x00FFFFFF : Synthetic COM objects, vtables, handles, and IAT thunks
 *   - 0x01000000..0x08FFFFFF : 128 MiB guest heap arena (sized for iPhone SE 2020 3 GB RAM)
 *   - 0x09000000..0x0FFFFFFF : Overflow/large texture/archive scratch heap (112 MiB)
 */

#include <cstddef>
#include <cstdint>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace mbaa_recomp {

class GuestMemory {
public:
    static constexpr uint32_t kArenaSize        = 0x10000000u; // 256 MiB VA space (0x00000000..0x0FFFFFFF)
    static constexpr uint32_t kTebBase          = 0x00300000u;
    static constexpr uint32_t kPebBase          = 0x00304000u;
    static constexpr uint32_t kImageBase        = 0x00400000u;
    static constexpr uint32_t kImageLimit       = 0x00800000u;
    static constexpr uint32_t kStackBase        = 0x00800000u; // 2 MiB stack bottom
    static constexpr uint32_t kStackTop         = 0x00A00000u; // 2 MiB stack top
    static constexpr uint32_t kInitialEsp       = 0x009FF000u;
    static constexpr uint32_t kThreadStackBase  = 0x00A00000u;
    static constexpr uint32_t kThreadStackSize  = 0x00040000u; // 256 KiB per worker thread
    static constexpr uint32_t kThreadStackLimit = 0x00E00000u;
    static constexpr uint32_t kThunkPageBase    = 0x00F00000u; // Synthetic COM / IAT thunk page
    static constexpr uint32_t kThunkPageLimit   = 0x01000000u;
    static constexpr uint32_t kComThunkBase     = 0x00F40000u; // Fixed COM method dispatch slot table
    static constexpr uint32_t kIatThunkBase     = 0x00FE0000u; // IAT indirect pointer targets (0x0051B000..0x0051B40C)
    static constexpr uint32_t kIatRangeStart    = 0x0051B000u;
    static constexpr uint32_t kIatRangeEnd      = 0x0051B410u;
    static constexpr uint32_t kHeapBase         = 0x01000000u; // 128 MiB main guest heap
    static constexpr uint32_t kHeapLimit        = 0x09000000u;
    static constexpr uint32_t kLargeHeapLimit   = 0x10000000u; // Extended ceiling for large allocations

    struct PeSectionInfo {
        std::string name;
        uint32_t va = 0;
        uint32_t virtual_size = 0;
        uint32_t raw_size = 0;
    };

    GuestMemory();
    ~GuestMemory();

    GuestMemory(const GuestMemory&) = delete;
    GuestMemory& operator=(const GuestMemory&) = delete;

    /// Initializes or resets the flat virtual arena, synthetic TEB/PEB, and allocators.
    bool init();
    void shutdown();

    /// Loads user's BYOC MBAA.exe headers & sections (.text/.rdata/.data/.rsrc/.new00) at exact VAs.
    /// Also patches IAT slots (0x0051B000..0x0051B40C) with synthetic kIatThunkBase targets.
    bool load_pe_sections(const std::string& exe_path);

    /// Validates that [va, va + size) falls within the 32-bit guest arena.
    [[nodiscard]] bool in_bounds(uint32_t va, size_t size = 1) const noexcept {
        return base_ != nullptr && static_cast<uint64_t>(va) + size <= kArenaSize;
    }

    // -----------------------------------------------------------------------
    // Typed little-endian guest memory accessors
    // -----------------------------------------------------------------------
    [[nodiscard]] uint8_t  r8(uint32_t va) const noexcept;
    [[nodiscard]] uint16_t r16(uint32_t va) const noexcept;
    [[nodiscard]] uint32_t r32(uint32_t va) const noexcept;
    [[nodiscard]] uint64_t r64(uint32_t va) const noexcept;
    [[nodiscard]] float    rf32(uint32_t va) const noexcept;
    [[nodiscard]] double   rf64(uint32_t va) const noexcept;

    void w8(uint32_t va, uint8_t v) noexcept;
    void w16(uint32_t va, uint16_t v) noexcept;
    void w32(uint32_t va, uint32_t v) noexcept;
    void w64(uint32_t va, uint64_t v) noexcept;
    void wf32(uint32_t va, float v) noexcept;
    void wf64(uint32_t va, double v) noexcept;

    /// Raw host pointer into guest arena (returns nullptr if out of bounds).
    [[nodiscard]] uint8_t* ptr(uint32_t va) noexcept;
    [[nodiscard]] const uint8_t* ptr(uint32_t va) const noexcept;
    [[nodiscard]] const uint8_t* cptr(uint32_t va) const noexcept { return ptr(va); }

    bool read_bytes(uint32_t va, void* dst, size_t size) const noexcept;
    bool write_bytes(uint32_t va, const void* src, size_t size) noexcept;
    bool zero_bytes(uint32_t va, size_t size) noexcept;

    [[nodiscard]] std::string read_cstring(uint32_t va, size_t max_len = 4096) const;
    [[nodiscard]] std::u16string read_wstring_utf16(uint32_t va, size_t max_chars = 2048) const;
    uint32_t write_cstring(uint32_t va, const std::string& s, size_t max_bytes = 0) noexcept;

    // -----------------------------------------------------------------------
    // Guest heap, thunk, and thread stack allocators (thread-safe)
    // -----------------------------------------------------------------------
    uint32_t guest_alloc(uint32_t size, uint32_t align = 16);
    uint32_t guest_calloc(uint32_t count, uint32_t size);
    uint32_t guest_realloc(uint32_t va, uint32_t new_size);
    void     guest_free(uint32_t va);
    [[nodiscard]] uint32_t guest_msize(uint32_t va) const;

    /// Allocates persistent synthetic objects/vtables inside 0x00F00000..0x00F3FFFF.
    uint32_t alloc_thunk_block(uint32_t size, uint32_t align = 16);

    /// Allocates a 256 KiB stack for a spawned guest worker thread and returns its initial ESP.
    uint32_t alloc_thread_stack();
    /// Recycles or frees a worker thread stack previously returned by `alloc_thread_stack()`.
    void free_thread_stack(uint32_t initial_esp);

    [[nodiscard]] uint32_t heap_used_bytes() const noexcept;
    [[nodiscard]] const std::vector<PeSectionInfo>& loaded_sections() const noexcept { return sections_; }
    [[nodiscard]] const std::string& last_error() const noexcept { return last_error_; }

private:
    static constexpr uint32_t kMinAllocAlign        = 16u;
    static constexpr uint32_t kThreadStackSlotCount = (kThreadStackLimit - kThreadStackBase) / kThreadStackSize;
    static_assert(kThreadStackSlotCount <= 32u, "Thread stack bitmask assumes <= 32 fixed slots");

    uint8_t* base_ = nullptr;
    bool     using_mmap_ = false;
    uint32_t host_page_size_ = 16384u;

    mutable std::mutex alloc_mutex_;
    uint32_t heap_cursor_              = kHeapBase;
    uint32_t thunk_cursor_             = kThunkPageBase;
    uint32_t heap_used_bytes_          = 0u;
    uint32_t active_thread_stack_mask_ = 0u;
    std::unordered_map<uint32_t, uint32_t> active_allocs_;
    std::map<uint32_t, uint32_t> free_blocks_;               // va -> size (coalesced, never touches heap_cursor_)
    std::set<std::pair<uint32_t, uint32_t>> free_by_size_;   // (size, va) for O(log N) best-fit / lowest-VA reuse
    std::unordered_set<uint32_t> active_overflow_stacks_;

    std::vector<PeSectionInfo> sections_;
    std::string last_error_;

    void     init_synthetic_teb_peb();
    void     patch_iat_thunks();
    uint32_t guest_alloc_locked(uint32_t size, uint32_t align);
    void     guest_free_locked(uint32_t va);
    void     insert_free_block_locked(uint32_t va, uint32_t size);
    void     erase_free_block_locked(uint32_t va, uint32_t size);
    void     free_range_locked(uint32_t va, uint32_t size);
    void     advise_reclaimable_locked(uint32_t va, uint32_t size, uint32_t min_bytes) noexcept;
};

} // namespace mbaa_recomp
