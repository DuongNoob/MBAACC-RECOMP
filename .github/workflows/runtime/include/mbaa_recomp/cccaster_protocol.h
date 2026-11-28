#pragma once

/**
 * @file cccaster_protocol.h
 * @brief Native C++20 CCCaster v3.1 UDP wire protocol, GoBackN reliable transport,
 *        RFC 1321 MD5 / zlib framing, and POSIX/Win32 socket client.
 *
 * Wire layouts, framing headers, version constants, PingStats math, and state transitions
 * are derived directly from read-only disassembly of CCCaster v3.1 (`cccaster.v3.1.exe`,
 * build "3.1.008" / "0a71d76" / "Thu Feb 26 15:57:16 EST 2026") and empirical validation
 * against shipped compressed artifacts.
 *
 * Windows Named Pipes (`\\.\pipe\cccaster_pipe`), loopback IPC, and `SocketShareData (0x17)`
 * are intentionally bypassed in-process on iOS/POSIX targets.
 */

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace mbaa_recomp {

// -----------------------------------------------------------------------------
// Compiled CCCaster v3.1 constants (verified in cccaster.v3.1.exe .rdata/.bss)
// -----------------------------------------------------------------------------

inline constexpr const char* kCccasterVersionString = "3.1.008";
inline constexpr const char* kCccasterGitRevision   = "0a71d76";
inline constexpr const char* kCccasterBuildDate     = "Thu Feb 26 15:57:16 EST 2026";

inline constexpr uint16_t kCccasterDefaultPort      = 3939u;  // 0 = OS ephemeral port when hosting
inline constexpr uint32_t kCccasterResendMs         = 50u;    // GoBackN::resendPeriod = 0x32 ms
inline constexpr uint32_t kCccasterTimeoutMs        = 20000u; // GoBackN::timeout = 0x4e20 ms
inline constexpr uint32_t kCccasterPingIntervalMs   = 250u;   // Calibration/keepalive Ping cadence
inline constexpr uint32_t kCccasterMaxChunkBytes    = 256u;   // SplitMessage chunk cap
inline constexpr size_t   kCccasterInputWindow      = 30u;    // PlayerInputs/BothInputs window
inline constexpr uint8_t  kCccasterMaxDelay         = 254u;   // config.ini maxRealDelay = 254
inline constexpr uint8_t  kCccasterMaxRollback      = 15u;    // hook.dll 0x6654433c cap
inline constexpr uint8_t  kCccasterDefaultRollback  = 4u;     // config.ini defaultRollback = 4
inline constexpr size_t   kCccasterRngStateBytes    = 232u;   // 3*u32 + 220B MBAA RNG slice
inline constexpr size_t   kCccasterMaxWirePacket    = 65536u; // Safety bound for decoded rawLen
inline constexpr size_t   kCccasterPingCalibSamples = 4u;     // Samples before Host emits NetplayConfig

// Per-frame uint16_t input word layout (matching hle_input_ios.mm & hook.dll 0x663a8090)
inline constexpr uint16_t kCccasterDirMask          = 0x000Fu; // Numpad 1..4, 6..9; 0/5/>9 -> 0
inline constexpr uint16_t kCccasterBtnStart         = 0x0010u; // bit 4
inline constexpr uint16_t kCccasterBtnAutoConfirm   = 0x0020u; // bit 5 (masked for spectators)
inline constexpr uint16_t kCccasterBtnD             = 0x0040u; // bit 6
inline constexpr uint16_t kCccasterBtnC             = 0x0080u; // bit 7
inline constexpr uint16_t kCccasterBtnA             = 0x0100u; // bit 8
inline constexpr uint16_t kCccasterBtnB             = 0x0200u; // bit 9
inline constexpr uint16_t kCccasterBtnAB            = 0x0400u; // bit 10 (A+B macro / Dash)
inline constexpr uint16_t kCccasterBtnE             = 0x0800u; // bit 11
inline constexpr uint16_t kCccasterBtnFN1           = 0x1000u; // bit 12
inline constexpr uint16_t kCccasterBtnFN2           = 0x2000u; // bit 13
inline constexpr uint16_t kCccasterBtnConfirm       = 0x4000u; // bit 14 (Menu confirm)
inline constexpr uint16_t kCccasterBtnCancel        = 0x8000u; // bit 15 (Menu cancel)

// -----------------------------------------------------------------------------
// Protocol Enums (wire values verified against 0x006d31b4 & class vtables)
// -----------------------------------------------------------------------------

enum class CccasterMsgType : uint8_t {
    AckSequence        = 0x01,
    BothInputs         = 0x02,
    ChangeConfig       = 0x03,
    ClientMode         = 0x04,
    ConfirmConfig      = 0x05,
    ControllerMappings = 0x06,
    ErrorMessage       = 0x07,
    GoBackNState       = 0x08,
    InitialConfig      = 0x09,
    InitialGameState   = 0x0a,
    IpAddrPort         = 0x0b,
    IpcConnected       = 0x0c,
    JoystickMappings   = 0x0d,
    KeyboardEvent      = 0x0e,
    KeyboardMappings   = 0x0f,
    MenuIndex          = 0x10,
    NetplayConfig      = 0x11,
    OptionsMessage     = 0x12,
    Ping               = 0x13, // Unreliable Message (0B base)
    PingStats          = 0x14,
    PlayerInputs       = 0x15, // Unreliable Message (0B base)
    RngState           = 0x16,
    SocketShareData    = 0x17, // Windows-only IPC; unsupported on iOS
    SpectateConfig     = 0x18,
    SplitMessage       = 0x19,
    Statistics         = 0x1a,
    SyncHash           = 0x1b,
    TestMessage        = 0x1c,
    UdpControl         = 0x1d,
    Version            = 0x1e,
    VersionConfig      = 0x1f,
    JoysticksChanged   = 0x20, // Unreliable Message (0B base)
    TransitionIndex    = 0x21, // Unreliable Message (0B base)
    PaletteManager     = 0x22,
};

enum class CccasterUdpControlCode : uint8_t {
    Unknown        = 0,
    ConnectRequest = 1,
    ConnectReply   = 2,
    ConnectFinal   = 3,
    Disconnect     = 4, // Bypass GoBackN, sent 3x on disconnect
};

enum class CccasterClientMode : uint8_t {
    Unknown           = 0,
    Host              = 1,
    Client            = 2,
    SpectateNetplay   = 3,
    SpectateBroadcast = 4,
    Broadcast         = 5,
    Offline           = 6,
};

enum class CccasterChangeKind : uint8_t {
    DelayP1  = 1, // NetplayManager +0x28 (%u P1 delay)
    DelayP2  = 2, // NetplayManager +0x29 (%u P2 delay)
    Rollback = 3, // NetplayManager +0x2a (%u rollback)
};

enum class CccasterSessionState : uint8_t {
    Offline     = 0,
    Listening   = 1,
    Connecting  = 2,
    Handshaking = 3,
    Connected   = 4,
    InGame      = 5,
    Error       = 6,
};

enum CccasterModeFlags : uint8_t {
    kModeFlagNone         = 0x00,
    kModeFlagTraining     = 0x01,
    kModeFlagDelayedSpec  = 0x20,
};

// -----------------------------------------------------------------------------
// Verified Wire Message Data Structures
// -----------------------------------------------------------------------------

struct CccasterStatistics {
    uint32_t sample_count   = 0u;
    double   max_one_way_ms = 0.0;
    double   mean_one_way_ms = 0.0;
    double   welford_m2     = 0.0;
    uint8_t  loss_percent   = 0u;

    void reset() noexcept;
    void record_rtt_ms(uint64_t rtt_ms) noexcept;
    [[nodiscard]] double stddev_ms() const noexcept;
    [[nodiscard]] uint16_t auto_delay(bool is_host_initial = false) const noexcept;
};

struct WireVersionConfig {
    uint32_t           seq_id         = 0u;
    CccasterClientMode mode           = CccasterClientMode::Unknown; // +0x38
    uint8_t            flags          = 0u;                          // +0x39
    std::string        version_str    = kCccasterVersionString;      // +0x58
    std::string        commit_str     = kCccasterGitRevision;        // +0x70
    std::string        build_date_str = kCccasterBuildDate;          // +0x88
};

struct WireInitialConfig {
    uint32_t           seq_id        = 0u;
    CccasterClientMode mode          = CccasterClientMode::Unknown; // +0x38
    uint8_t            flags         = 0u;                          // +0x39
    uint16_t           spectate_port = 0u;                          // +0x3c
    std::string        local_name;                                  // +0x40
    std::string        remote_name;                                 // +0x58
    uint8_t            extra_flag    = 0u;                          // +0x70
};

struct WireNetplayConfig {
    uint32_t           seq_id      = 0u;
    CccasterClientMode mode        = CccasterClientMode::Host; // +0x38
    uint8_t            flags       = 0u;                       // +0x39
    uint8_t            delay       = 0u;                       // +0x3c
    uint8_t            rollback    = kCccasterDefaultRollback; // +0x3d
    uint8_t            sub_byte_3e = 0u;                       // +0x3e
    uint8_t            sub_byte_3f = 0u;                       // +0x3f
    uint8_t            host_side   = 1u;                       // +0x40 (1 = Host is P1, 2 = Host is P2)
    uint16_t           sub_word_42 = 2u;                       // +0x42 (versusWinCount/session word)
    std::string        p1_name;                                // +0x44
    std::string        p2_name;                                // +0x5c
    std::string        session_tag;                            // +0x74 (10-char tag from 0x0059f070)
    std::string        extra_tag;                              // +0x8c
    uint32_t           tail_word_a4 = 0u;                      // +0xa4
};

struct WireSpectateConfig {
    uint32_t           seq_id       = 0u;
    CccasterClientMode mode         = CccasterClientMode::SpectateNetplay; // +0x38
    uint8_t            flags        = 0u;                                  // +0x39
    uint8_t            delay        = 0u;                                  // +0x3c
    uint8_t            rollback     = kCccasterDefaultRollback;            // +0x3d
    uint8_t            sub_byte_3e  = 0u;                                  // +0x3e
    uint8_t            sub_byte_3f  = 0u;                                  // +0x3f
    std::string        p1_name;                                            // +0x40
    std::string        p2_name;                                            // +0x58
    std::string        session_tag;                                        // +0x70
    std::array<uint8_t, 8> state_header8{};                                // +0xa8
    uint32_t           stage        = 0u;                                  // +0xb0
    uint8_t            state_u8_b4  = 0u;                                  // +0xb4
    uint8_t            state_u8_b5  = 0u;                                  // +0xb5
    uint16_t           chara_word   = 0u;                                  // +0xb6
    uint16_t           moon_word    = 0u;                                  // +0xb8
    uint16_t           color_word   = 0u;                                  // +0xba
};

struct WireChangeConfig {
    uint32_t           seq_id   = 0u;
    CccasterChangeKind kind     = CccasterChangeKind::DelayP1; // +0x1c
    std::array<uint8_t, 8> payload8{};                         // +0x20
    uint8_t            delay    = 0u;                          // +0x28
    uint8_t            p2_delay = 0u;                          // +0x29
    uint8_t            rollback = kCccasterDefaultRollback;    // +0x2a
};

struct WireInitialGameState {
    uint32_t seq_id = 0u;
    std::array<uint8_t, 8> header8{}; // +0x20
    uint32_t stage       = 0u;        // +0x28
    uint8_t  round_flags = 0u;        // +0x2c
    uint8_t  unk_2d      = 0u;        // +0x2d
    uint8_t  chara0      = 0u;        // +0x2e
    uint8_t  chara1      = 0u;        // +0x2f
    uint8_t  moon0       = 0u;        // +0x30
    uint8_t  moon1       = 0u;        // +0x31
    uint8_t  color0      = 0u;        // +0x32
    uint8_t  color1      = 0u;        // +0x33
};

struct WirePlayerInputs {
    uint32_t frame = 0xFFFFFFFFu; // Message (0B base), +0x18; 0xFFFFFFFF = empty
    uint32_t index = 0u;          // +0x1c
    std::array<uint16_t, kCccasterInputWindow> inputs{}; // Fixed 60B on wire (+0x20)
};

struct WireBothInputs {
    uint32_t seq_id = 0u;
    uint32_t frame  = 0xFFFFFFFFu; // +0x20
    uint32_t index  = 0u;          // +0x24
    std::array<uint16_t, kCccasterInputWindow> p1_inputs{}; // Fixed 60B on wire (+0x28)
    std::array<uint16_t, kCccasterInputWindow> p2_inputs{}; // Fixed 60B on wire (+0x64)
};

struct WireRngState {
    uint32_t seq_id  = 0u;
    uint32_t context = 0u; // +0x1c
    // Layout of data[0..232):
    //   [0..4)    uint32_t seed_563778
    //   [4..8)    uint32_t seed_56377c
    //   [8..12)   uint32_t idx_564068
    //   [12..232) uint8_t  table_564070[220]
    std::array<uint8_t, kCccasterRngStateBytes> data{};
};

struct WireSyncHash {
    uint32_t seq_id         = 0u;
    uint32_t indexed_frame  = 0u; // +0x20
    uint32_t round_or_flags = 0u; // +0x24
    std::array<uint8_t, 16>  rng_md5{};  // +0x28: MD5 of 232B RngState
    std::array<uint32_t, 4>  globals{};  // +0x38..+0x44: 0x562a3c, 0x562a40, 0x564b14, 0x564b18
    std::array<uint8_t, 44>  p1_slice{}; // +0x48..+0x73
    std::array<uint8_t, 44>  p2_slice{}; // +0x74..+0x9f
};

struct WireMenuIndex {
    uint32_t seq_id        = 0u;
    uint32_t indexed_frame = 0u;  // +0x1c
    int8_t   menu_choice   = -1;  // +0x20 (-1 / 0xff = unset)
};

struct WireSplitMessage {
    uint32_t             seq_id        = 0u;
    CccasterMsgType      orig_msg_type = CccasterMsgType::AckSequence; // +0x1c
    uint32_t             part_idx      = 0u;                           // +0x38
    uint32_t             total_parts   = 0u;                           // +0x3c
    std::vector<uint8_t> chunk;                                        // +0x20 (lenStr, <=256B)
};

// -----------------------------------------------------------------------------
// Pure Helper Primitives (RFC 1321 MD5, Framing, Version, Auto-Delay, IPv4)
// -----------------------------------------------------------------------------

/// Returns primary non-loopback local IPv4 address string via POSIX/Apple `getifaddrs`
/// (falls back to `"127.0.0.1"` if no non-loopback IPv4 interface is up).
[[nodiscard]] std::string cccaster_get_local_ipv4();

/// Self-contained RFC 1321 MD5 over `[data, data + len)`.
[[nodiscard]] std::array<uint8_t, 16> cccaster_md5(const uint8_t* data, size_t len) noexcept;

/// Returns true iff `type` derives from `Sequence` (leading `uint32_t seqId`),
/// false for unreliable `Message` types (`0x0e, 0x13, 0x15, 0x20, 0x21`).
[[nodiscard]] bool cccaster_is_sequence_msg(CccasterMsgType type) noexcept;

/// Implements `Version::isCompatible` (`0x00494f90`): rejects legacy `"2.1e"`/`"3.0a.019"`,
/// requires `major.minor == "3.1"` (`strict_version=false`) or `"3.1.008"` (`strict_version=true`).
[[nodiscard]] bool cccaster_version_compatible(const std::string& remote_ver,
                                               const std::string& remote_build_date,
                                               bool strict_version = false);

/// Serializes `[msgType][compLevel][comp header if smaller][payload || MD5(body)]` matching
/// `Protocol::encode` (`0x0047b5b0` / `0x0047ac40`), with compression threshold `(compLen + 8) < rawLen`.
[[nodiscard]] std::vector<uint8_t> cccaster_encode_packet(CccasterMsgType msg_type,
                                                          const std::vector<uint8_t>& body,
                                                          int zlib_level = 9);

/// Decodes an outer `Protocol::encode` packet, handling both `compLevel == 0` and zlib
/// (`compLevel != 0`) streams, and verifies the trailing 16-byte RFC 1321 MD5 digest.
[[nodiscard]] bool cccaster_decode_packet(const uint8_t* data,
                                          size_t len,
                                          CccasterMsgType& out_type,
                                          std::vector<uint8_t>& out_body,
                                          bool* out_md5_ok = nullptr);

/// Normalizes numpad bits (`0..3`: `0`, `5`, or `>9` -> `0`) and optionally clears
/// auto-confirm bit `0x0020` for spectators/replays.
[[nodiscard]] uint16_t cccaster_sanitize_input_word(uint16_t raw_word,
                                                    bool mask_spectator_auto_confirm = false) noexcept;

/// Exact CCCaster delay math: `ceil(0.06 * mean_one_way_ms)` (+1 for Host initial config),
/// clamped to `<= 254` (`maxRealDelay`).
[[nodiscard]] uint16_t cccaster_compute_auto_delay(double mean_one_way_ms,
                                                   bool is_host_initial = false) noexcept;

// Wire body encode/decode helpers (exposed for isolated protocol unit verification)
[[nodiscard]] std::vector<uint8_t> serialize_player_inputs(const WirePlayerInputs& msg);
[[nodiscard]] bool deserialize_player_inputs(const std::vector<uint8_t>& body, WirePlayerInputs& out);

[[nodiscard]] std::vector<uint8_t> serialize_both_inputs(const WireBothInputs& msg);
[[nodiscard]] bool deserialize_both_inputs(const std::vector<uint8_t>& body, WireBothInputs& out);

[[nodiscard]] std::vector<uint8_t> serialize_ping_stats(uint32_t seq_id, const CccasterStatistics& stats);
[[nodiscard]] bool deserialize_ping_stats(const std::vector<uint8_t>& body,
                                          uint32_t& out_seq_id,
                                          CccasterStatistics& out_stats);

[[nodiscard]] std::vector<uint8_t> serialize_rng_state(const WireRngState& msg);
[[nodiscard]] bool deserialize_rng_state(const std::vector<uint8_t>& body, WireRngState& out);

[[nodiscard]] std::vector<uint8_t> serialize_sync_hash(const WireSyncHash& msg);
[[nodiscard]] bool deserialize_sync_hash(const std::vector<uint8_t>& body, WireSyncHash& out);

// -----------------------------------------------------------------------------
// Netplay / Spectate Session Configuration, Live Status & Client Class
// -----------------------------------------------------------------------------

struct CccasterSessionConfig {
    std::string peer_ip;
    uint16_t    port           = kCccasterDefaultPort; // 0 = ephemeral OS port when hosting
    std::string player_name    = "iOS";
    int         delay_frames   = -1;                   // -1 = Auto from RTT; 0..254 = fixed
    int         max_rollback   = kCccasterDefaultRollback; // 0..15
    bool        training_mode  = false;
    bool        strict_version = false;                // Matches config.ini StrictVersion=0
    bool        host_plays_p1  = true;                 // Host = P1 (side 1), Client = P2 (side 2)
    uint16_t    spectate_port  = 0u;                   // Optional host broadcast UDP port (0 = disabled)
};

struct CccasterSessionStatus {
    CccasterClientMode   mode                  = CccasterClientMode::Offline;
    CccasterSessionState state                 = CccasterSessionState::Offline;
    bool                 active                = false;
    bool                 connected             = false;
    bool                 in_match              = false;
    bool                 is_host               = false;
    int                  local_player_index    = -1;    // 0 = P1, 1 = P2, -1 = spectate/offline
    uint16_t             local_port            = 0u;
    std::string          local_ipv4;
    std::string          peer_addr;
    std::string          peer_name;
    std::string          p1_name;
    std::string          p2_name;
    std::string          session_tag;
    double               ping_ms               = 0.0;   // Latest RTT estimate (ms)
    double               one_way_ms            = 0.0;   // Mean one-way latency (ms)
    double               max_one_way_ms        = 0.0;   // Peak one-way latency (ms)
    double               jitter_ms             = 0.0;   // Welford sample stddev (ms)
    uint8_t              packet_loss_percent   = 0u;
    uint32_t             ping_samples          = 0u;
    int                  delay_frames          = 0;
    int                  max_rollback          = kCccasterDefaultRollback;
    uint32_t             confirmed_remote_frame = 0xFFFFFFFFu;
    uint32_t             last_sent_frame       = 0xFFFFFFFFu;
    uint32_t             spectator_count       = 0u;
    std::string          state_label;
    std::string          last_error;
};

/**
 * Thread-safe, non-blocking CCCaster v3.1 UDP protocol client supporting Host, Join,
 * and Spectate roles with full GoBackN reliable sequencing (`50 ms` resend, `20000 ms`
 * timeout, `>256 B` `SplitMessage 0x19` fragmentation), 3-way `UdpControl` handshake,
 * `VersionConfig`, `Ping`/`PingStats` RTT/delay calibration, 30-frame `PlayerInputs` /
 * `BothInputs` sliding redundancy, `RngState` (`232 B`), `SyncHash` (`160 B`), and
 * spectator stream support.
 */
class CccasterNetClient {
public:
    CccasterNetClient();
    ~CccasterNetClient();

    CccasterNetClient(const CccasterNetClient&) = delete;
    CccasterNetClient& operator=(const CccasterNetClient&) = delete;

    /// Returns monotonic steady-clock milliseconds used internally when `now_ms == 0`.
    [[nodiscard]] static uint64_t steady_clock_ms() noexcept;

    bool start_host(const CccasterSessionConfig& config);
    bool start_join(const CccasterSessionConfig& config);
    bool start_spectate(const CccasterSessionConfig& config);
    void disconnect();

    /// Non-blocking UDP I/O pump, GoBackN resend/timeout tick, and handshake state machine.
    /// Pass `now_ms = 0` to sample `steady_clock_ms()` automatically.
    void poll(uint64_t now_ms = 0u);

    /// Sends 30-frame redundant `PlayerInputs (0x15)` window (or caches local spectate input).
    void submit_local_input(uint32_t frame, uint16_t input_word, uint32_t context_index = 0u);

    /// Looks up the latest received remote player input for `frame`.
    [[nodiscard]] bool get_remote_input(uint32_t frame, uint16_t& out_input_word) const;

    /// Looks up `(p1, p2)` inputs for `frame` when connected in Spectate mode (`BothInputs 0x02`).
    [[nodiscard]] bool get_spectate_inputs(uint32_t frame,
                                           uint16_t& out_p1_word,
                                           uint16_t& out_p2_word) const;

    /// Broadcasts confirmed `(p1, p2)` inputs (`BothInputs 0x02`) to connected spectators.
    void broadcast_both_inputs(uint32_t frame,
                               uint16_t p1_input_word,
                               uint16_t p2_input_word,
                               uint32_t context_index = 0u);

    bool send_rng_state(const WireRngState& state);
    [[nodiscard]] bool pop_remote_rng_state(WireRngState& out_state);

    bool send_sync_hash(const WireSyncHash& hash);
    [[nodiscard]] bool pop_remote_sync_hash(WireSyncHash& out_hash);

    bool send_initial_game_state(const WireInitialGameState& state);
    [[nodiscard]] bool pop_remote_initial_game_state(WireInitialGameState& out_state);

    bool send_menu_index(uint32_t indexed_frame, int8_t menu_choice);
    [[nodiscard]] bool pop_remote_menu_index(WireMenuIndex& out_menu);

    bool send_transition_index(uint32_t transition_id);
    [[nodiscard]] bool pop_remote_transition_index(uint32_t& out_transition_id);

    bool send_change_config(const WireChangeConfig& cfg);
    [[nodiscard]] bool pop_remote_change_config(WireChangeConfig& out_cfg);

    [[nodiscard]] CccasterSessionStatus status() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

} // namespace mbaa_recomp
