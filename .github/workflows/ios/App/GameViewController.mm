#import "GameViewController.h"
#import "TouchOverlayView.h"

#import <GameController/GameController.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#include "mbaa_recomp/hle_input.h"
#include "mbaa_recomp/runtime_engine.h"

#include <arpa/inet.h>

#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>

// NSUserDefaults keys for the CCCaster v3.1 netplay form.
static NSString* const kNetplayDefaultsMode     = @"MBAACCNetplayMode";
static NSString* const kNetplayDefaultsName     = @"MBAACCNetplayName";
static NSString* const kNetplayDefaultsIP       = @"MBAACCNetplayPeerIP";
static NSString* const kNetplayDefaultsPort     = @"MBAACCNetplayPort";
static NSString* const kNetplayDefaultsDelay    = @"MBAACCNetplayDelay";
static NSString* const kNetplayDefaultsRollback = @"MBAACCNetplayRollback";

static const NSInteger kNetplayModeHost     = 0;
static const NSInteger kNetplayModeJoin     = 1;
static const NSInteger kNetplayModeSpectate = 2;

static const int kNetplayUiMaxDelay    = 10;  // UI cap; engine/protocol accept up to 254
static const int kNetplayUiMaxRollback = 15;  // CCCaster hook.dll cap (0x0f)
static const NSUInteger kNetplayMaxNameLength = 24;

static NSString* NetplayNSString(const std::string& s) {
    NSString* r = [NSString stringWithUTF8String:s.c_str()];
    return r ?: @"";
}

static bool NetplayParseInt(NSString* text, long lo, long hi, int* out) {
    const char* p = text.UTF8String;
    if (!p || *p == '\0') return false;
    errno = 0;
    char* end = nullptr;
    long v = std::strtol(p, &end, 10);
    if (errno != 0 || end == p || *end != '\0' || v < lo || v > hi) return false;
    *out = (int)v;
    return true;
}

static bool NetplayIsValidIPv4(NSString* text) {
    const char* p = text.UTF8String;
    if (!p) return false;
    struct in_addr addr;
    return inet_pton(AF_INET, p, &addr) == 1;
}

static NSString* NetplayStateName(const mbaa_recomp::NetplayStatus& st) {
    if (!st.state_label.empty()) return NetplayNSString(st.state_label);
    switch (st.state) {
        case mbaa_recomp::NetplayConnState::Offline:     return @"Offline";
        case mbaa_recomp::NetplayConnState::Listening:   return @"Listening";
        case mbaa_recomp::NetplayConnState::Connecting:  return @"Connecting";
        case mbaa_recomp::NetplayConnState::Handshaking: return @"Handshaking";
        case mbaa_recomp::NetplayConnState::Connected:   return @"Connected";
        case mbaa_recomp::NetplayConnState::InGame:      return @"In game";
        case mbaa_recomp::NetplayConnState::Error:       return @"Error";
    }
    return @"Unknown";
}

@interface GameViewController () <TouchOverlayViewDelegate, UITextFieldDelegate, UIGestureRecognizerDelegate>

@property (nonatomic, strong) MTKView* metalView;
@property (nonatomic, strong) TouchOverlayView* touchOverlay;
@property (nonatomic, strong) UIView* onboardingView;
@property (nonatomic, strong) UILabel* onboardingStatusLabel;
@property (nonatomic, strong) UIView* pauseOverlayView;
@property (nonatomic, strong) UITextView* pauseDebugTextView;
@property (nonatomic, strong) UIButton* debugCopyButton;

// CCCaster v3.1 netplay panel + HUD
@property (nonatomic, strong) UIView* netplayPanelView;
@property (nonatomic, strong) UIScrollView* netplayScrollView;
@property (nonatomic, strong) UISegmentedControl* netplayModeControl;
@property (nonatomic, strong) UIButton* netplayLocalIPButton;
@property (nonatomic, strong) UIView* netplayIPContainer;
@property (nonatomic, strong) UITextField* netplayIPField;
@property (nonatomic, strong) UITextField* netplayPortField;
@property (nonatomic, strong) UITextField* netplayNameField;
@property (nonatomic, strong) UITextField* netplayDelayField;
@property (nonatomic, strong) UITextField* netplayRollbackField;
@property (nonatomic, strong) UITextView* netplayStatusTextView;
@property (nonatomic, strong) UIButton* netplayPrimaryButton;
@property (nonatomic, strong) UIButton* netplayDisconnectButton;
@property (nonatomic, strong) UILabel* netplayHudLabel;
@property (nonatomic, strong) NSTimer* netplayRefreshTimer;

@property (nonatomic, assign) BOOL assetsReady;
@property (nonatomic, assign) BOOL engineStarted;
@property (nonatomic, assign) BOOL pausedBySystem;
@property (nonatomic, assign) BOOL pausedByUser;
@property (nonatomic, copy) NSString* resolvedAssetsDir;

@end

@implementation GameViewController {
    std::unique_ptr<mbaa_recomp::RuntimeEngine> _engine;
    NSString* _netplayFormMessage;      // last validation / start error shown in the panel
    NSString* _netplayCachedLocalIPv4;  // refreshed on panel open / mode change (getifaddrs is not per-tick)
}

#pragma mark - Lifecycle & iOS Hardware Policy (iPhone SE 2020)

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor blackColor];

    [self setupMetalView];
    [self setupTouchOverlay];
    [self setupPauseOverlay];
    [self setupNetplayUI];
    [self setupOnboardingView];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleAppBecameActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];

    [self checkBYOCAssetsAndBootIfReady];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [_netplayRefreshTimer invalidate];
    [self shutdownEngine];
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (BOOL)prefersHomeIndicatorAutoHidden {
    return YES;
}

- (UIRectEdge)preferredScreenEdgesDeferringSystemGestures {
    return UIRectEdgeAll;
}

- (UIInterfaceOrientationMask)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskLandscape;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Critical on iPhone SE 2020 (3 GB RAM): evict LRU textures and trim transient caches.
    if (_engine && _engineStarted) {
        _engine->handle_memory_warning();
    }
}

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    [self updateViewportAndOverlayLayout];
}

- (void)setPausedBySystem:(BOOL)paused {
    _pausedBySystem = paused;
    self.metalView.paused = (paused || _pausedByUser || !_assetsReady);
}

- (void)shutdownEngine {
    [_netplayRefreshTimer invalidate];
    _netplayRefreshTimer = nil;
    if (_engine && _engineStarted) {
        _engine->stop_netplay();
        _engine->shutdown();
        _engineStarted = NO;
    }
    _engine.reset();
    _netplayHudLabel.hidden = YES;
}

#pragma mark - Metal View & 4:3 Viewport (1000x750 centered in 1334x750)

- (void)setupMetalView {
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    _metalView = [[MTKView alloc] initWithFrame:self.view.bounds device:device];
    _metalView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _metalView.delegate = self;
    _metalView.preferredFramesPerSecond = 60;
    _metalView.colorPixelFormat = MTLPixelFormatBGRA8Unorm;
    _metalView.clearColor = MTLClearColorMake(0.0, 0.0, 0.0, 1.0);
    _metalView.enableSetNeedsDisplay = NO;
    _metalView.paused = YES;

    if ([_metalView.layer isKindOfClass:[CAMetalLayer class]]) {
        CAMetalLayer* metalLayer = (CAMetalLayer*)_metalView.layer;
        metalLayer.pixelFormat = MTLPixelFormatBGRA8Unorm;
    }

    [self.view addSubview:_metalView];
}

- (void)setupTouchOverlay {
    _touchOverlay = [[TouchOverlayView alloc] initWithFrame:self.view.bounds];
    _touchOverlay.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _touchOverlay.delegate = self;
    _touchOverlay.hidden = YES;
    [self.view addSubview:_touchOverlay];
}

- (CGRect)centeredGameViewportRectInBounds:(CGRect)bounds {
    CGFloat w = bounds.size.width;
    CGFloat h = bounds.size.height;
    if (w <= 0.0 || h <= 0.0) {
        return CGRectZero;
    }
    // 4:3 aspect-preserving viewport: on iPhone SE 2020 (667x375 pt / 1334x750 px),
    // this yields 500x375 pt (1000x750 px) centered, leaving 83.5 pt (167 px) per sidebar.
    CGFloat vpW = MIN(w, h * (4.0 / 3.0));
    CGFloat vpH = vpW * (3.0 / 4.0);
    return CGRectMake((w - vpW) * 0.5, (h - vpH) * 0.5, vpW, vpH);
}

- (void)updateViewportAndOverlayLayout {
    CGRect vpRect = [self centeredGameViewportRectInBounds:self.view.bounds];
    [_touchOverlay updateLayoutForViewportRect:vpRect];
}

#pragma mark - BYOC Asset Checker (Documents/MBAACC/ or Documents/)

- (NSArray<NSString*>*)requiredBYOCFilenames {
    return @[
        @"MBAA.exe",
        @"0000.p", @"0001.p", @"0002.p", @"0003.p",
        @"0004.p", @"0005.p", @"0006.p", @"0007.p", @"0008.p"
    ];
}

- (nullable NSString*)findCaseInsensitiveEntry:(NSString*)targetName inDirectory:(NSString*)dirPath {
    NSFileManager* fm = [NSFileManager defaultManager];
    NSArray<NSString*>* items = [fm contentsOfDirectoryAtPath:dirPath error:nil];
    for (NSString* item in items) {
        if ([item caseInsensitiveCompare:targetName] == NSOrderedSame) {
            return [dirPath stringByAppendingPathComponent:item];
        }
    }
    return nil;
}

- (NSString*)documentsDirectoryPath {
    NSArray<NSString*>* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    return paths.firstObject ?: NSTemporaryDirectory();
}

- (void)ensureDocumentsMBAACCFolderExists {
    NSString* mbaaccDir = [[self documentsDirectoryPath] stringByAppendingPathComponent:@"MBAACC"];
    NSFileManager* fm = [NSFileManager defaultManager];
    if (![fm fileExistsAtPath:mbaaccDir]) {
        [fm createDirectoryAtPath:mbaaccDir withIntermediateDirectories:YES attributes:nil error:nil];
    }
}

- (void)checkBYOCAssetsAndBootIfReady {
    [self ensureDocumentsMBAACCFolderExists];

    NSString* docsDir = [self documentsDirectoryPath];
    NSString* subDir = [docsDir stringByAppendingPathComponent:@"MBAACC"];

    // Prefer Documents/MBAACC/, fallback to Documents/ directly if user dropped files at root.
    NSArray<NSString*>* candidates = @[ subDir, docsDir ];
    NSString* chosenDir = subDir;
    NSInteger bestFoundCount = -1;

    for (NSString* dir in candidates) {
        NSInteger found = 0;
        for (NSString* req in [self requiredBYOCFilenames]) {
            if ([self findCaseInsensitiveEntry:req inDirectory:dir] != nil) {
                found++;
            }
        }
        if (found > bestFoundCount) {
            bestFoundCount = found;
            chosenDir = dir;
        }
    }

    self.resolvedAssetsDir = chosenDir;

    NSMutableArray<NSString*>* missing = [NSMutableArray array];
    NSMutableString* report = [NSMutableString string];
    NSFileManager* fm = [NSFileManager defaultManager];

    [report appendFormat:@"Thư mục kiểm tra / Active folder:\n%@\n\n", chosenDir];
    [report appendString:@"Tệp bắt buộc / Required BYOC files:\n"];

    for (NSString* req in [self requiredBYOCFilenames]) {
        NSString* resolved = [self findCaseInsensitiveEntry:req inDirectory:chosenDir];
        if (resolved != nil) {
            NSDictionary* attrs = [fm attributesOfItemAtPath:resolved error:nil];
            unsigned long long sizeMB = [attrs[NSFileSize] unsignedLongLongValue] / (1024ULL * 1024ULL);
            [report appendFormat:@"  [OK]      %@ (%llu MiB)\n", req, sizeMB];
        } else {
            [report appendFormat:@"  [MISSING] %@\n", req];
            [missing addObject:req];
        }
    }

    [report appendString:@"\nThư mục bổ sung / Optional asset folders:\n"];
    for (NSString* optDir in @[ @"System", @"Information", @"GRP", @"dat", @"Movie" ]) {
        NSString* resolved = [self findCaseInsensitiveEntry:optDir inDirectory:chosenDir];
        BOOL isDir = NO;
        BOOL exists = (resolved != nil && [fm fileExistsAtPath:resolved isDirectory:&isDir] && isDir);
        [report appendFormat:@"  %@ %@/\n", exists ? @"[OK]     " : @"[WARN]   ", optDir];
    }

    if (missing.count == 0) {
        _assetsReady = YES;
        _onboardingView.hidden = YES;
        _touchOverlay.hidden = NO;
        [self bootRuntimeEngineIfNeeded];
    } else {
        _assetsReady = NO;
        _metalView.paused = YES;
        _touchOverlay.hidden = YES;
        _onboardingView.hidden = NO;
        _onboardingStatusLabel.text = report;
    }
}

- (void)handleAppBecameActive:(NSNotification*)note {
    (void)note;
    if (!_assetsReady) {
        [self checkBYOCAssetsAndBootIfReady];
    }
}

#pragma mark - Onboarding UI (Bilingual Vietnamese / English)

- (void)setupOnboardingView {
    _onboardingView = [[UIView alloc] initWithFrame:self.view.bounds];
    _onboardingView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _onboardingView.backgroundColor = [UIColor colorWithRed:0.06 green:0.07 blue:0.10 alpha:1.0];

    UIScrollView* scroll = [[UIScrollView alloc] initWithFrame:self.view.bounds];
    scroll.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    [_onboardingView addSubview:scroll];

    UIStackView* stack = [[UIStackView alloc] init];
    stack.axis = UILayoutConstraintAxisVertical;
    stack.spacing = 10.0;
    stack.translatesAutoresizingMaskIntoConstraints = NO;
    [scroll addSubview:stack];

    [NSLayoutConstraint activateConstraints:@[
        [stack.topAnchor constraintEqualToAnchor:scroll.contentLayoutGuide.topAnchor constant:20.0],
        [stack.bottomAnchor constraintEqualToAnchor:scroll.contentLayoutGuide.bottomAnchor constant:-20.0],
        [stack.leadingAnchor constraintEqualToAnchor:scroll.frameLayoutGuide.leadingAnchor constant:28.0],
        [stack.trailingAnchor constraintEqualToAnchor:scroll.frameLayoutGuide.trailingAnchor constant:-28.0],
    ]];

    UILabel* title = [[UILabel alloc] init];
    title.text = @"MBAACC Recompiled — BYOC Asset Setup (iPhone SE 2020)";
    title.font = [UIFont systemFontOfSize:18.0 weight:UIFontWeightBold];
    title.textColor = [UIColor whiteColor];
    title.numberOfLines = 0;
    [stack addArrangedSubview:title];

    UILabel* guide = [[UILabel alloc] init];
    guide.numberOfLines = 0;
    guide.font = [UIFont systemFontOfSize:13.0 weight:UIFontWeightRegular];
    guide.textColor = [UIColor colorWithWhite:0.88 alpha:1.0];
    guide.text =
        @"VN: Ứng dụng không đính kèm tệp game bản quyền (BYOC). Hãy mở ứng dụng Tệp (Files) "
        @"trên iOS hoặc Finder -> Tệp trên macOS, chép MBAA.exe, 0000.p .. 0008.p, cùng thư mục "
        @"System/ và Information/ từ bản MBAACC PC vào thư mục: Trên iPhone -> MBAACC -> MBAACC/\n\n"
        @"EN: Bring Your Own Copy — copy MBAA.exe, 0000.p..0008.p, System/, and Information/ from "
        @"your legal PC installation into On My iPhone -> MBAACC -> MBAACC/ via iOS Files or macOS Finder.";
    [stack addArrangedSubview:guide];

    _onboardingStatusLabel = [[UILabel alloc] init];
    _onboardingStatusLabel.numberOfLines = 0;
    _onboardingStatusLabel.font = [UIFont monospacedSystemFontOfSize:11.5 weight:UIFontWeightRegular];
    _onboardingStatusLabel.textColor = [UIColor colorWithRed:0.72 green:0.90 blue:1.0 alpha:1.0];
    _onboardingStatusLabel.backgroundColor = [UIColor colorWithWhite:0.12 alpha:1.0];
    _onboardingStatusLabel.layer.cornerRadius = 8.0;
    _onboardingStatusLabel.layer.masksToBounds = YES;
    [stack addArrangedSubview:_onboardingStatusLabel];

    UIButton* rescanBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* rescanCfg = [UIButtonConfiguration filledButtonConfiguration];
    rescanCfg.title = @"Kiểm tra lại / Re-scan Documents/MBAACC/";
    rescanCfg.baseBackgroundColor = [UIColor colorWithRed:0.16 green:0.48 blue:0.92 alpha:1.0];
    rescanCfg.baseForegroundColor = [UIColor whiteColor];
    rescanCfg.cornerStyle = UIButtonConfigurationCornerStyleMedium;
    rescanCfg.contentInsets = NSDirectionalEdgeInsetsMake(12, 18, 12, 18);
    rescanBtn.configuration = rescanCfg;
    [rescanBtn addTarget:self action:@selector(onRescanTapped) forControlEvents:UIControlEventTouchUpInside];
    [stack addArrangedSubview:rescanBtn];

    [self.view addSubview:_onboardingView];
}

- (void)onRescanTapped {
    [self checkBYOCAssetsAndBootIfReady];
}

#pragma mark - Pause Overlay

- (void)setupPauseOverlay {
    _pauseOverlayView = [[UIView alloc] initWithFrame:self.view.bounds];
    _pauseOverlayView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _pauseOverlayView.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.68];
    _pauseOverlayView.hidden = YES;

    UIStackView* card = [[UIStackView alloc] init];
    card.axis = UILayoutConstraintAxisVertical;
    card.spacing = 8.0;
    card.alignment = UIStackViewAlignmentFill;
    card.translatesAutoresizingMaskIntoConstraints = NO;
    card.backgroundColor = [UIColor colorWithWhite:0.12 alpha:0.95];
    card.layer.cornerRadius = 14.0;
    card.layoutMargins = UIEdgeInsetsMake(14, 18, 14, 18);
    card.layoutMarginsRelativeArrangement = YES;
    [_pauseOverlayView addSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [card.centerXAnchor constraintEqualToAnchor:_pauseOverlayView.centerXAnchor],
        [card.centerYAnchor constraintEqualToAnchor:_pauseOverlayView.centerYAnchor],
        [card.widthAnchor constraintEqualToConstant:460.0],
    ]];

    UILabel* label = [[UILabel alloc] init];
    label.text = @"PAUSED / TẠM DỪNG";
    label.textAlignment = NSTextAlignmentCenter;
    label.textColor = [UIColor whiteColor];
    label.font = [UIFont systemFontOfSize:16.0 weight:UIFontWeightBold];
    [card addArrangedSubview:label];

    _pauseDebugTextView = [[UITextView alloc] init];
    _pauseDebugTextView.editable = NO;
    _pauseDebugTextView.selectable = YES;
    _pauseDebugTextView.font = [UIFont monospacedSystemFontOfSize:10.5 weight:UIFontWeightRegular];
    _pauseDebugTextView.textColor = [UIColor colorWithRed:0.76 green:0.94 blue:1.0 alpha:1.0];
    _pauseDebugTextView.backgroundColor = [UIColor colorWithWhite:0.06 alpha:1.0];
    _pauseDebugTextView.layer.cornerRadius = 8.0;
    _pauseDebugTextView.textContainerInset = UIEdgeInsetsMake(6, 6, 6, 6);
    _pauseDebugTextView.text = @"Waiting for RuntimeEngine telemetry...";
    [_pauseDebugTextView.heightAnchor constraintEqualToConstant:84.0].active = YES;
    [card addArrangedSubview:_pauseDebugTextView];

    UIButton* resumeBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* resumeCfg = [UIButtonConfiguration filledButtonConfiguration];
    resumeCfg.title = @"Resume / Tiếp tục";
    resumeCfg.baseBackgroundColor = [UIColor colorWithRed:0.18 green:0.55 blue:0.92 alpha:1.0];
    resumeCfg.baseForegroundColor = [UIColor whiteColor];
    resumeCfg.cornerStyle = UIButtonConfigurationCornerStyleMedium;
    resumeCfg.contentInsets = NSDirectionalEdgeInsetsMake(8, 14, 8, 14);
    resumeBtn.configuration = resumeCfg;
    [resumeBtn addTarget:self action:@selector(onResumeTapped) forControlEvents:UIControlEventTouchUpInside];
    [card addArrangedSubview:resumeBtn];

    _debugCopyButton = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* copyCfg = [UIButtonConfiguration filledButtonConfiguration];
    copyCfg.title = @"Copy Debug Log / Chép Log";
    copyCfg.baseBackgroundColor = [UIColor colorWithRed:0.16 green:0.46 blue:0.32 alpha:1.0];
    copyCfg.baseForegroundColor = [UIColor whiteColor];
    copyCfg.cornerStyle = UIButtonConfigurationCornerStyleMedium;
    copyCfg.contentInsets = NSDirectionalEdgeInsetsMake(8, 14, 8, 14);
    _debugCopyButton.configuration = copyCfg;
    [_debugCopyButton addTarget:self action:@selector(onCopyDebugLogTapped) forControlEvents:UIControlEventTouchUpInside];
    [card addArrangedSubview:_debugCopyButton];

    UIButton* trimBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* trimCfg = [UIButtonConfiguration filledButtonConfiguration];
    trimCfg.title = @"Trim GPU Memory Cache";
    trimCfg.baseBackgroundColor = [UIColor colorWithWhite:0.22 alpha:1.0];
    trimCfg.baseForegroundColor = [UIColor whiteColor];
    trimCfg.cornerStyle = UIButtonConfigurationCornerStyleMedium;
    trimCfg.contentInsets = NSDirectionalEdgeInsetsMake(8, 14, 8, 14);
    trimBtn.configuration = trimCfg;
    [trimBtn addTarget:self action:@selector(onTrimMemoryTapped) forControlEvents:UIControlEventTouchUpInside];
    [card addArrangedSubview:trimBtn];

    UIButton* netplayBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* netplayCfg = [UIButtonConfiguration filledButtonConfiguration];
    netplayCfg.title = @"Online Netplay (CCCaster v3.1)";
    netplayCfg.baseBackgroundColor = [UIColor colorWithRed:0.50 green:0.28 blue:0.78 alpha:1.0];
    netplayCfg.baseForegroundColor = [UIColor whiteColor];
    netplayCfg.cornerStyle = UIButtonConfigurationCornerStyleMedium;
    netplayCfg.contentInsets = NSDirectionalEdgeInsetsMake(8, 14, 8, 14);
    netplayBtn.configuration = netplayCfg;
    [netplayBtn addTarget:self action:@selector(onNetplayButtonTapped) forControlEvents:UIControlEventTouchUpInside];
    [card addArrangedSubview:netplayBtn];

    [self.view addSubview:_pauseOverlayView];
}

- (void)refreshPauseDebugSummary {
    if (_engine && _engineStarted) {
        std::string summary = _engine->debug_summary();
        NSString* text = [NSString stringWithUTF8String:summary.c_str()];
        _pauseDebugTextView.text = text ?: @"(unable to decode debug summary)";
    } else {
        _pauseDebugTextView.text = @"RuntimeEngine is not started yet.";
    }
}

- (void)onCopyDebugLogTapped {
    [self refreshPauseDebugSummary];
    [UIPasteboard generalPasteboard].string = _pauseDebugTextView.text ?: @"";
    UIButtonConfiguration* cfg = _debugCopyButton.configuration;
    cfg.title = @"Copied! / Đã chép";
    _debugCopyButton.configuration = cfg;
    __weak GameViewController* weakSelf = self;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        GameViewController* strongSelf = weakSelf;
        if (!strongSelf) return;
        UIButtonConfiguration* restore = strongSelf.debugCopyButton.configuration;
        restore.title = @"Copy Debug Log / Chép Log";
        strongSelf.debugCopyButton.configuration = restore;
    });
}

- (void)onResumeTapped {
    [self closeNetplayPanel];
    _pausedByUser = NO;
    _pauseOverlayView.hidden = YES;
    self.metalView.paused = (_pausedBySystem || !_assetsReady);
}

- (void)onTrimMemoryTapped {
    if (_engine && _engineStarted) {
        _engine->handle_memory_warning();
        [self refreshPauseDebugSummary];
    }
}

#pragma mark - Online Netplay (CCCaster v3.1) Panel & HUD

- (UIColor*)netplayFieldBackgroundColor {
    return [UIColor colorWithWhite:0.22 alpha:1.0];
}

- (UITextField*)makeNetplayFieldWithText:(NSString*)text
                             placeholder:(NSString*)placeholder
                                keyboard:(UIKeyboardType)keyboard {
    UITextField* field = [[UITextField alloc] init];
    field.text = text;
    field.attributedPlaceholder = [[NSAttributedString alloc]
        initWithString:placeholder
            attributes:@{ NSForegroundColorAttributeName : [UIColor colorWithWhite:1.0 alpha:0.35] }];
    field.font = [UIFont monospacedSystemFontOfSize:13.0 weight:UIFontWeightRegular];
    field.textColor = [UIColor whiteColor];
    field.backgroundColor = [self netplayFieldBackgroundColor];
    field.layer.cornerRadius = 6.0;
    field.borderStyle = UITextBorderStyleNone;
    field.keyboardType = keyboard;
    field.keyboardAppearance = UIKeyboardAppearanceDark;
    field.returnKeyType = UIReturnKeyDone;
    field.autocapitalizationType = UITextAutocapitalizationTypeNone;
    field.autocorrectionType = UITextAutocorrectionTypeNo;
    field.spellCheckingType = UITextSpellCheckingTypeNo;
    field.clearButtonMode = UITextFieldViewModeWhileEditing;
    field.leftView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 7, 1)];
    field.leftViewMode = UITextFieldViewModeAlways;
    field.delegate = self;
    [field.heightAnchor constraintEqualToConstant:30.0].active = YES;
    return field;
}

- (UIStackView*)wrapNetplayField:(UITextField*)field caption:(NSString*)caption {
    UILabel* cap = [[UILabel alloc] init];
    cap.text = caption;
    cap.font = [UIFont systemFontOfSize:10.0 weight:UIFontWeightSemibold];
    cap.textColor = [UIColor colorWithWhite:1.0 alpha:0.62];
    UIStackView* v = [[UIStackView alloc] initWithArrangedSubviews:@[ cap, field ]];
    v.axis = UILayoutConstraintAxisVertical;
    v.spacing = 2.0;
    return v;
}

- (UIButton*)makeNetplayActionButtonWithTitle:(NSString*)title color:(UIColor*)color action:(SEL)action {
    UIButton* btn = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* cfg = [UIButtonConfiguration filledButtonConfiguration];
    cfg.title = title;
    cfg.baseBackgroundColor = color;
    cfg.baseForegroundColor = [UIColor whiteColor];
    cfg.cornerStyle = UIButtonConfigurationCornerStyleMedium;
    cfg.contentInsets = NSDirectionalEdgeInsetsMake(7, 8, 7, 8);
    cfg.titleTextAttributesTransformer = ^NSDictionary<NSAttributedStringKey, id>*(NSDictionary<NSAttributedStringKey, id>* attrs) {
        NSMutableDictionary<NSAttributedStringKey, id>* out = [NSMutableDictionary dictionaryWithDictionary:attrs];
        out[NSFontAttributeName] = [UIFont systemFontOfSize:13.0 weight:UIFontWeightSemibold];
        return out;
    };
    btn.configuration = cfg;
    [btn addTarget:self action:action forControlEvents:UIControlEventTouchUpInside];
    return btn;
}

- (void)setupNetplayUI {
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    mbaa_recomp::NetplayConfig base{};

    NSString* savedName = [defaults stringForKey:kNetplayDefaultsName];
    if (savedName.length == 0) savedName = NetplayNSString(base.player_name);
    NSString* savedIP = [defaults stringForKey:kNetplayDefaultsIP] ?: @"";
    NSString* savedPort = [defaults stringForKey:kNetplayDefaultsPort];
    if (savedPort.length == 0) savedPort = [NSString stringWithFormat:@"%u", (unsigned)base.port];
    NSString* savedDelay = [defaults stringForKey:kNetplayDefaultsDelay];
    if (savedDelay.length == 0) savedDelay = @"Auto";
    NSString* savedRollback = [defaults stringForKey:kNetplayDefaultsRollback];
    if (savedRollback.length == 0) savedRollback = [NSString stringWithFormat:@"%d", base.max_rollback];
    NSInteger savedMode = [defaults integerForKey:kNetplayDefaultsMode];
    if (savedMode < kNetplayModeHost || savedMode > kNetplayModeSpectate) savedMode = kNetplayModeHost;

    // --- Live HUD pill (top-center, hidden while offline, never intercepts touches) ---
    _netplayHudLabel = [[UILabel alloc] init];
    _netplayHudLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _netplayHudLabel.font = [UIFont monospacedSystemFontOfSize:10.0 weight:UIFontWeightSemibold];
    _netplayHudLabel.textColor = [UIColor colorWithWhite:1.0 alpha:0.92];
    _netplayHudLabel.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.52];
    _netplayHudLabel.textAlignment = NSTextAlignmentCenter;
    _netplayHudLabel.layer.cornerRadius = 8.0;
    _netplayHudLabel.layer.masksToBounds = YES;
    _netplayHudLabel.userInteractionEnabled = NO;
    _netplayHudLabel.hidden = YES;
    [self.view addSubview:_netplayHudLabel];
    [NSLayoutConstraint activateConstraints:@[
        [_netplayHudLabel.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],
        [_netplayHudLabel.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor constant:2.0],
        [_netplayHudLabel.heightAnchor constraintEqualToConstant:17.0],
    ]];

    // --- Panel: dim backdrop + compact card with a scrollable form ---
    _netplayPanelView = [[UIView alloc] initWithFrame:self.view.bounds];
    _netplayPanelView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _netplayPanelView.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.72];
    _netplayPanelView.hidden = YES;
    [self.view addSubview:_netplayPanelView];

    UITapGestureRecognizer* backgroundTap =
        [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onNetplayBackgroundTapped)];
    backgroundTap.cancelsTouchesInView = NO;
    backgroundTap.delegate = self;
    [_netplayPanelView addGestureRecognizer:backgroundTap];

    UIView* card = [[UIView alloc] init];
    card.translatesAutoresizingMaskIntoConstraints = NO;
    card.backgroundColor = [UIColor colorWithWhite:0.12 alpha:0.97];
    card.layer.cornerRadius = 14.0;
    card.layer.masksToBounds = YES;
    card.overrideUserInterfaceStyle = UIUserInterfaceStyleDark;
    [_netplayPanelView addSubview:card];

    UILayoutGuide* safe = _netplayPanelView.safeAreaLayoutGuide;
    NSLayoutConstraint* preferredHeight = [card.heightAnchor constraintEqualToConstant:330.0];
    preferredHeight.priority = 750;
    NSLayoutConstraint* preferredWidth = [card.widthAnchor constraintEqualToConstant:520.0];
    preferredWidth.priority = 750;
    NSLayoutConstraint* preferredCenterY = [card.centerYAnchor constraintEqualToAnchor:_netplayPanelView.centerYAnchor];
    preferredCenterY.priority = 500;
    [NSLayoutConstraint activateConstraints:@[
        [card.centerXAnchor constraintEqualToAnchor:_netplayPanelView.centerXAnchor],
        preferredWidth,
        [card.widthAnchor constraintLessThanOrEqualToConstant:520.0],
        [card.leadingAnchor constraintGreaterThanOrEqualToAnchor:safe.leadingAnchor constant:12.0],
        [card.trailingAnchor constraintLessThanOrEqualToAnchor:safe.trailingAnchor constant:-12.0],
        [card.topAnchor constraintGreaterThanOrEqualToAnchor:safe.topAnchor constant:6.0],
        [card.bottomAnchor constraintLessThanOrEqualToAnchor:safe.bottomAnchor constant:-6.0],
        // Keep the card above the software keyboard (iPhone SE landscape: ~half the screen).
        [card.bottomAnchor constraintLessThanOrEqualToAnchor:self.view.keyboardLayoutGuide.topAnchor constant:-6.0],
        preferredHeight,
        preferredCenterY,
    ]];

    UILabel* title = [[UILabel alloc] init];
    title.translatesAutoresizingMaskIntoConstraints = NO;
    title.text = @"Online Netplay (CCCaster v3.1)";
    title.textColor = [UIColor whiteColor];
    title.font = [UIFont systemFontOfSize:14.0 weight:UIFontWeightBold];
    [card addSubview:title];

    _netplayScrollView = [[UIScrollView alloc] init];
    _netplayScrollView.translatesAutoresizingMaskIntoConstraints = NO;
    _netplayScrollView.keyboardDismissMode = UIScrollViewKeyboardDismissModeInteractive;
    _netplayScrollView.alwaysBounceVertical = YES;
    [card addSubview:_netplayScrollView];

    [NSLayoutConstraint activateConstraints:@[
        [title.topAnchor constraintEqualToAnchor:card.topAnchor constant:10.0],
        [title.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:14.0],
        [title.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-14.0],
        [_netplayScrollView.topAnchor constraintEqualToAnchor:title.bottomAnchor constant:6.0],
        [_netplayScrollView.leadingAnchor constraintEqualToAnchor:card.leadingAnchor],
        [_netplayScrollView.trailingAnchor constraintEqualToAnchor:card.trailingAnchor],
        [_netplayScrollView.bottomAnchor constraintEqualToAnchor:card.bottomAnchor],
    ]];

    UIStackView* form = [[UIStackView alloc] init];
    form.axis = UILayoutConstraintAxisVertical;
    form.spacing = 8.0;
    form.translatesAutoresizingMaskIntoConstraints = NO;
    [_netplayScrollView addSubview:form];
    [NSLayoutConstraint activateConstraints:@[
        [form.topAnchor constraintEqualToAnchor:_netplayScrollView.contentLayoutGuide.topAnchor constant:2.0],
        [form.bottomAnchor constraintEqualToAnchor:_netplayScrollView.contentLayoutGuide.bottomAnchor constant:-12.0],
        [form.leadingAnchor constraintEqualToAnchor:_netplayScrollView.frameLayoutGuide.leadingAnchor constant:14.0],
        [form.trailingAnchor constraintEqualToAnchor:_netplayScrollView.frameLayoutGuide.trailingAnchor constant:-14.0],
    ]];

    // Mode: Host / Join / Spectate
    _netplayModeControl = [[UISegmentedControl alloc] initWithItems:@[ @"Host", @"Join", @"Spectate" ]];
    _netplayModeControl.selectedSegmentIndex = savedMode;
    _netplayModeControl.selectedSegmentTintColor = [UIColor colorWithRed:0.50 green:0.28 blue:0.78 alpha:1.0];
    NSDictionary* segAttrs = @{ NSForegroundColorAttributeName : [UIColor whiteColor],
                                NSFontAttributeName : [UIFont systemFontOfSize:13.0 weight:UIFontWeightSemibold] };
    [_netplayModeControl setTitleTextAttributes:segAttrs forState:UIControlStateNormal];
    [_netplayModeControl setTitleTextAttributes:segAttrs forState:UIControlStateSelected];
    [_netplayModeControl addTarget:self action:@selector(onNetplayModeChanged) forControlEvents:UIControlEventValueChanged];
    [_netplayModeControl.heightAnchor constraintEqualToConstant:30.0].active = YES;
    [form addArrangedSubview:_netplayModeControl];

    // Host-only: local IPv4 (LAN / Tailscale / ZeroTier) — tap copies "ip:port"
    _netplayLocalIPButton = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* localCfg = [UIButtonConfiguration plainButtonConfiguration];
    localCfg.title = @"Local IPv4: ...";
    localCfg.baseForegroundColor = [UIColor colorWithRed:0.62 green:0.86 blue:1.0 alpha:1.0];
    localCfg.contentInsets = NSDirectionalEdgeInsetsMake(2, 0, 2, 0);
    localCfg.titleTextAttributesTransformer = ^NSDictionary<NSAttributedStringKey, id>*(NSDictionary<NSAttributedStringKey, id>* attrs) {
        NSMutableDictionary<NSAttributedStringKey, id>* out = [NSMutableDictionary dictionaryWithDictionary:attrs];
        out[NSFontAttributeName] = [UIFont monospacedSystemFontOfSize:12.0 weight:UIFontWeightMedium];
        return out;
    };
    _netplayLocalIPButton.configuration = localCfg;
    _netplayLocalIPButton.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeading;
    [_netplayLocalIPButton addTarget:self action:@selector(onNetplayCopyAddressTapped) forControlEvents:UIControlEventTouchUpInside];
    [form addArrangedSubview:_netplayLocalIPButton];

    // Row 1: IP Address (hidden in Host mode) | Port
    _netplayIPField = [self makeNetplayFieldWithText:savedIP placeholder:@"192.168.1.20 or 100.x.y.z"
                                            keyboard:UIKeyboardTypeNumbersAndPunctuation];
    _netplayPortField = [self makeNetplayFieldWithText:savedPort placeholder:@"Port"
                                              keyboard:UIKeyboardTypeNumbersAndPunctuation];
    _netplayIPContainer = [self wrapNetplayField:_netplayIPField caption:@"IP ADDRESS"];
    UIStackView* portContainer = [self wrapNetplayField:_netplayPortField caption:@"PORT"];
    [portContainer.widthAnchor constraintEqualToConstant:84.0].active = YES;
    [_netplayIPContainer setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    UIStackView* row1 = [[UIStackView alloc] initWithArrangedSubviews:@[ _netplayIPContainer, portContainer ]];
    row1.axis = UILayoutConstraintAxisHorizontal;
    row1.spacing = 8.0;
    row1.alignment = UIStackViewAlignmentTop;
    [form addArrangedSubview:row1];

    // Row 2: Name | Delay | Rollback
    _netplayNameField = [self makeNetplayFieldWithText:savedName placeholder:@"Name" keyboard:UIKeyboardTypeDefault];
    _netplayDelayField = [self makeNetplayFieldWithText:savedDelay placeholder:@"Auto" keyboard:UIKeyboardTypeDefault];
    _netplayRollbackField = [self makeNetplayFieldWithText:savedRollback placeholder:@"0-15"
                                                  keyboard:UIKeyboardTypeNumbersAndPunctuation];
    UIStackView* nameContainer = [self wrapNetplayField:_netplayNameField caption:@"NAME"];
    UIStackView* delayContainer = [self wrapNetplayField:_netplayDelayField caption:@"DELAY (AUTO/0-10)"];
    UIStackView* rollbackContainer = [self wrapNetplayField:_netplayRollbackField caption:@"ROLLBACK (0-15)"];
    [delayContainer.widthAnchor constraintEqualToConstant:112.0].active = YES;
    [rollbackContainer.widthAnchor constraintEqualToConstant:104.0].active = YES;
    [nameContainer setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
    UIStackView* row2 = [[UIStackView alloc] initWithArrangedSubviews:@[ nameContainer, delayContainer, rollbackContainer ]];
    row2.axis = UILayoutConstraintAxisHorizontal;
    row2.spacing = 8.0;
    row2.alignment = UIStackViewAlignmentTop;
    [form addArrangedSubview:row2];

    // Live status
    _netplayStatusTextView = [[UITextView alloc] init];
    _netplayStatusTextView.editable = NO;
    _netplayStatusTextView.selectable = NO;
    _netplayStatusTextView.scrollEnabled = NO;
    _netplayStatusTextView.font = [UIFont monospacedSystemFontOfSize:10.5 weight:UIFontWeightRegular];
    _netplayStatusTextView.textColor = [UIColor colorWithRed:0.76 green:0.94 blue:1.0 alpha:1.0];
    _netplayStatusTextView.backgroundColor = [UIColor colorWithWhite:0.06 alpha:1.0];
    _netplayStatusTextView.layer.cornerRadius = 8.0;
    _netplayStatusTextView.textContainerInset = UIEdgeInsetsMake(6, 6, 6, 6);
    _netplayStatusTextView.text = @"State: Offline";
    [form addArrangedSubview:_netplayStatusTextView];

    // Actions: Start Host / Join / Spectate | Disconnect | Close
    _netplayPrimaryButton = [self makeNetplayActionButtonWithTitle:@"Start Host"
                                                             color:[UIColor colorWithRed:0.18 green:0.55 blue:0.92 alpha:1.0]
                                                            action:@selector(onNetplayPrimaryTapped)];
    _netplayDisconnectButton = [self makeNetplayActionButtonWithTitle:@"Disconnect"
                                                                color:[UIColor colorWithRed:0.72 green:0.22 blue:0.22 alpha:1.0]
                                                               action:@selector(onNetplayDisconnectTapped)];
    UIButton* closeBtn = [self makeNetplayActionButtonWithTitle:@"Close"
                                                          color:[UIColor colorWithWhite:0.28 alpha:1.0]
                                                         action:@selector(onNetplayCloseTapped)];
    UIStackView* actions = [[UIStackView alloc] initWithArrangedSubviews:@[ _netplayPrimaryButton, _netplayDisconnectButton, closeBtn ]];
    actions.axis = UILayoutConstraintAxisHorizontal;
    actions.spacing = 8.0;
    actions.distribution = UIStackViewDistributionFillEqually;
    [form addArrangedSubview:actions];

    UILabel* hint = [[UILabel alloc] init];
    hint.numberOfLines = 0;
    hint.font = [UIFont systemFontOfSize:10.0 weight:UIFontWeightRegular];
    hint.textColor = [UIColor colorWithWhite:1.0 alpha:0.5];
    hint.text = @"LAN / Tailscale / ZeroTier / port-forwarded UDP. The handshake keeps running while the game is paused; "
                @"Close, then Resume to play. / Kết nối vẫn chạy khi tạm dừng; bấm Close rồi Resume để chơi.";
    [form addArrangedSubview:hint];

    [self applyNetplayModeLayout];
}

- (NSInteger)selectedNetplayMode {
    return _netplayModeControl.selectedSegmentIndex;
}

- (void)applyNetplayModeLayout {
    NSInteger mode = [self selectedNetplayMode];
    _netplayIPContainer.hidden = (mode == kNetplayModeHost);
    _netplayLocalIPButton.hidden = (mode != kNetplayModeHost);

    NSString* primaryTitle = (mode == kNetplayModeHost) ? @"Start Host"
                           : (mode == kNetplayModeJoin) ? @"Join" : @"Spectate";
    UIButtonConfiguration* cfg = _netplayPrimaryButton.configuration;
    cfg.title = primaryTitle;
    _netplayPrimaryButton.configuration = cfg;
}

- (void)onNetplayModeChanged {
    [self.view endEditing:YES];
    _netplayFormMessage = nil;
    _netplayCachedLocalIPv4 = NetplayNSString(mbaa_recomp::RuntimeEngine::get_local_ipv4());
    [self applyNetplayModeLayout];
    [self refreshNetplayUI];
}

- (void)onNetplayButtonTapped {
    [self.view endEditing:YES];
    _netplayFormMessage = nil;
    _netplayCachedLocalIPv4 = NetplayNSString(mbaa_recomp::RuntimeEngine::get_local_ipv4());
    [self applyNetplayModeLayout];
    _netplayPanelView.hidden = NO;
    [self.view bringSubviewToFront:_netplayPanelView];
    [_netplayScrollView setContentOffset:CGPointZero animated:NO];
    [self refreshNetplayUI];
}

- (void)closeNetplayPanel {
    [self.view endEditing:YES];
    _netplayPanelView.hidden = YES;
}

- (void)onNetplayCloseTapped {
    [self closeNetplayPanel];
}

- (void)onNetplayBackgroundTapped {
    [self.view endEditing:YES];
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer*)gestureRecognizer shouldReceiveTouch:(UITouch*)touch {
    (void)gestureRecognizer;
    // Let text fields, buttons and the segmented control handle their own taps.
    return ![touch.view isKindOfClass:[UIControl class]];
}

- (BOOL)textFieldShouldReturn:(UITextField*)textField {
    [textField resignFirstResponder];
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField*)textField {
    __weak GameViewController* weakSelf = self;
    __weak UITextField* weakField = textField;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.30 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        GameViewController* strongSelf = weakSelf;
        UITextField* field = weakField;
        if (!strongSelf || !field || !field.isFirstResponder) return;
        CGRect r = [strongSelf.netplayScrollView convertRect:field.bounds fromView:field];
        [strongSelf.netplayScrollView scrollRectToVisible:CGRectInset(r, 0.0, -14.0) animated:YES];
    });
}

- (void)onNetplayCopyAddressTapped {
    mbaa_recomp::NetplayStatus st;
    if (_engine && _engineStarted) st = _engine->netplay_status();
    NSString* ip = (st.active && !st.local_ipv4.empty()) ? NetplayNSString(st.local_ipv4) : _netplayCachedLocalIPv4;
    if (ip.length == 0) return;
    NSString* port = (st.active && st.local_port != 0) ? [NSString stringWithFormat:@"%u", (unsigned)st.local_port]
                                                       : (_netplayPortField.text ?: @"");
    [UIPasteboard generalPasteboard].string = port.length ? [NSString stringWithFormat:@"%@:%@", ip, port] : ip;
}

/// Validates the form and fills `outConfig`. On failure returns NO and sets `outError`.
- (BOOL)buildNetplayConfig:(mbaa_recomp::NetplayConfig*)outConfig mode:(NSInteger)mode error:(NSString**)outError {
    NSCharacterSet* ws = [NSCharacterSet whitespaceAndNewlineCharacterSet];
    NSString* portText = [_netplayPortField.text stringByTrimmingCharactersInSet:ws];
    NSString* ipText = [_netplayIPField.text stringByTrimmingCharactersInSet:ws];

    // Accept a pasted "ip:port" (CCCaster style) in the IP field; its port wins.
    if (mode != kNetplayModeHost) {
        NSArray<NSString*>* parts = [ipText componentsSeparatedByString:@":"];
        if (parts.count == 2) {
            ipText = parts[0];
            portText = parts[1];
        } else if (parts.count > 2) {
            *outError = @"IP Address must be IPv4 (a.b.c.d or a.b.c.d:port).";
            return NO;
        }
    }

    int port = 0;
    long minPort = (mode == kNetplayModeHost) ? 0 : 1;
    if (!NetplayParseInt(portText, minPort, 65535, &port)) {
        *outError = (mode == kNetplayModeHost) ? @"Port must be 0..65535 (0 = pick a free port)."
                                               : @"Port must be 1..65535.";
        return NO;
    }

    if (mode != kNetplayModeHost && !NetplayIsValidIPv4(ipText)) {
        *outError = @"IP Address must be a valid IPv4 address (e.g. 192.168.1.20).";
        return NO;
    }

    NSString* name = [_netplayNameField.text stringByTrimmingCharactersInSet:ws];
    if (name.length > kNetplayMaxNameLength) name = [name substringToIndex:kNetplayMaxNameLength];
    if (name.length == 0) name = NetplayNSString(mbaa_recomp::NetplayConfig{}.player_name);

    int delay = -1;
    NSString* delayText = [[_netplayDelayField.text stringByTrimmingCharactersInSet:ws] lowercaseString];
    if (delayText.length != 0 && ![delayText isEqualToString:@"auto"]) {
        if (!NetplayParseInt(delayText, 0, kNetplayUiMaxDelay, &delay)) {
            *outError = @"Delay must be Auto or a number 0..10.";
            return NO;
        }
    }

    int rollback = 0;
    NSString* rollbackText = [_netplayRollbackField.text stringByTrimmingCharactersInSet:ws];
    if (!NetplayParseInt(rollbackText, 0, kNetplayUiMaxRollback, &rollback)) {
        *outError = @"Rollback must be a number 0..15.";
        return NO;
    }

    mbaa_recomp::NetplayConfig cfg{};
    cfg.peer_ip      = (mode == kNetplayModeHost) ? std::string() : std::string(ipText.UTF8String);
    cfg.port         = (uint16_t)port;
    cfg.player_name  = std::string(name.UTF8String);
    cfg.delay_frames = delay;
    cfg.max_rollback = rollback;
    *outConfig = cfg;

    // Normalize the visible fields to what is actually used and persist them.
    _netplayIPField.text = (mode == kNetplayModeHost) ? _netplayIPField.text : ipText;
    _netplayPortField.text = [NSString stringWithFormat:@"%d", port];
    _netplayNameField.text = name;
    _netplayDelayField.text = (delay < 0) ? @"Auto" : [NSString stringWithFormat:@"%d", delay];
    _netplayRollbackField.text = [NSString stringWithFormat:@"%d", rollback];

    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    [defaults setInteger:mode forKey:kNetplayDefaultsMode];
    [defaults setObject:name forKey:kNetplayDefaultsName];
    if (mode != kNetplayModeHost) [defaults setObject:ipText forKey:kNetplayDefaultsIP];
    [defaults setObject:_netplayPortField.text forKey:kNetplayDefaultsPort];
    [defaults setObject:_netplayDelayField.text forKey:kNetplayDefaultsDelay];
    [defaults setObject:_netplayRollbackField.text forKey:kNetplayDefaultsRollback];
    return YES;
}

- (void)onNetplayPrimaryTapped {
    [self.view endEditing:YES];
    if (!_engine || !_engineStarted) {
        _netplayFormMessage = @"Engine is not running (BYOC assets missing or init failed).";
        [self refreshNetplayUI];
        return;
    }

    NSInteger mode = [self selectedNetplayMode];
    mbaa_recomp::NetplayConfig cfg{};
    NSString* error = nil;
    if (![self buildNetplayConfig:&cfg mode:mode error:&error]) {
        _netplayFormMessage = error;
        [self refreshNetplayUI];
        return;
    }

    bool ok = false;
    if (mode == kNetplayModeHost) {
        ok = _engine->start_netplay_host(cfg);
    } else if (mode == kNetplayModeJoin) {
        ok = _engine->start_netplay_join(cfg);
    } else {
        ok = _engine->start_netplay_spectate(cfg);
    }

    if (ok) {
        _netplayFormMessage = nil;
    } else {
        mbaa_recomp::NetplayStatus st = _engine->netplay_status();
        NSString* detail = NetplayNSString(st.last_error);
        _netplayFormMessage = detail.length ? detail : @"Failed to start netplay session.";
    }
    [self refreshNetplayUI];
}

- (void)onNetplayDisconnectTapped {
    [self.view endEditing:YES];
    if (_engine && _engineStarted) {
        _engine->stop_netplay();
    }
    _netplayFormMessage = nil;
    [self refreshNetplayUI];
}

- (void)startNetplayRefreshTimer {
    [_netplayRefreshTimer invalidate];
    __weak GameViewController* weakSelf = self;
    NSTimer* timer = [NSTimer timerWithTimeInterval:0.25 repeats:YES block:^(NSTimer* t) {
        (void)t;
        [weakSelf refreshNetplayUI];
    }];
    timer.tolerance = 0.05;
    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
    _netplayRefreshTimer = timer;
}

- (void)refreshNetplayUI {
    const BOOL engineUp = (_engine && _engineStarted);
    mbaa_recomp::NetplayStatus st;
    if (engineUp) {
        st = _engine->netplay_status();
    }
    [self updateNetplayHudWithStatus:st engineUp:engineUp];
    if (!_netplayPanelView.hidden) {
        [self updateNetplayPanelWithStatus:st engineUp:engineUp];
    }
}

- (void)updateNetplayHudWithStatus:(const mbaa_recomp::NetplayStatus&)st engineUp:(BOOL)engineUp {
    if (!engineUp || !st.active) {
        _netplayHudLabel.hidden = YES;
        return;
    }
    NSString* text = nil;
    switch (st.state) {
        case mbaa_recomp::NetplayConnState::Listening:
            text = (st.local_port != 0) ? [NSString stringWithFormat:@"CC 3.1 | Host :%u", (unsigned)st.local_port]
                                        : @"CC 3.1 | Hosting";
            break;
        case mbaa_recomp::NetplayConnState::Connecting:
        case mbaa_recomp::NetplayConnState::Handshaking:
            text = @"CC 3.1 | Connecting...";
            break;
        case mbaa_recomp::NetplayConnState::Connected:
        case mbaa_recomp::NetplayConnState::InGame:
            text = [NSString stringWithFormat:@"CC 3.1 | %.0fms | D%d R%d", st.ping_ms, st.delay_frames, st.max_rollback];
            if (st.desync_count != 0) {
                text = [text stringByAppendingFormat:@" | DS%u", (unsigned)st.desync_count];
            }
            break;
        case mbaa_recomp::NetplayConnState::Error:
            text = @"CC 3.1 | Error";
            break;
        case mbaa_recomp::NetplayConnState::Offline:
            break;
    }
    if (!text) {
        _netplayHudLabel.hidden = YES;
        return;
    }
    NSString* padded = [NSString stringWithFormat:@"  %@  ", text];
    if (![_netplayHudLabel.text isEqualToString:padded]) {
        _netplayHudLabel.text = padded;
    }
    _netplayHudLabel.hidden = NO;
}

- (void)updateNetplayPanelWithStatus:(const mbaa_recomp::NetplayStatus&)st engineUp:(BOOL)engineUp {
    const BOOL active = engineUp && st.active;
    const BOOL formEnabled = !active;

    _netplayModeControl.enabled = formEnabled;
    _netplayIPField.enabled = formEnabled;
    _netplayPortField.enabled = formEnabled;
    _netplayNameField.enabled = formEnabled;
    _netplayDelayField.enabled = formEnabled;
    _netplayRollbackField.enabled = formEnabled;
    _netplayPrimaryButton.enabled = (engineUp && !active);
    _netplayDisconnectButton.enabled = active;

    // Host: show the address the peer should type (LAN / VPN IPv4 + port).
    NSString* ip = (active && !st.local_ipv4.empty()) ? NetplayNSString(st.local_ipv4) : _netplayCachedLocalIPv4;
    NSString* port = (active && st.local_port != 0) ? [NSString stringWithFormat:@"%u", (unsigned)st.local_port]
                                                    : (_netplayPortField.text ?: @"");
    NSString* localTitle = (ip.length == 0)
        ? @"Local IPv4: unavailable (join Wi-Fi / VPN)"
        : [NSString stringWithFormat:@"Local IPv4: %@%@%@  (tap to copy)", ip, port.length ? @":" : @"", port];
    UIButtonConfiguration* localCfg = _netplayLocalIPButton.configuration;
    if (![localCfg.title isEqualToString:localTitle]) {
        localCfg.title = localTitle;
        _netplayLocalIPButton.configuration = localCfg;
    }

    NSMutableString* text = [NSMutableString string];
    if (!engineUp) {
        [text appendString:@"State: Engine not running"];
    } else {
        NSString* peer = st.peer_addr.empty() ? @"-" : NetplayNSString(st.peer_addr);
        if (!st.peer_name.empty()) {
            peer = [NSString stringWithFormat:@"%@ (%@)", peer, NetplayNSString(st.peer_name)];
        }
        [text appendFormat:@"State: %@\n", NetplayStateName(st)];
        [text appendFormat:@"Peer: %@\n", peer];
        if (st.connected) {
            [text appendFormat:@"Ping: %.0f ms (one-way %.1f ms)\n", st.ping_ms, st.one_way_ms];
        } else {
            [text appendString:@"Ping: -\n"];
        }
        [text appendFormat:@"Delay: %d  Rollback: %d\n", st.delay_frames, st.max_rollback];
        [text appendFormat:@"Frame: %u  Rollbacks: %u  Desyncs: %u", (unsigned)st.current_frame,
                           (unsigned)st.rollback_count, (unsigned)st.desync_count];
        if (!st.last_error.empty()) {
            [text appendFormat:@"\nError: %@", NetplayNSString(st.last_error)];
        }
    }
    if (_netplayFormMessage.length) {
        [text appendFormat:@"\n! %@", _netplayFormMessage];
    }
    if (![_netplayStatusTextView.text isEqualToString:text]) {
        _netplayStatusTextView.text = text;
    }
}

#pragma mark - RuntimeEngine & MTKViewDelegate

- (void)bootRuntimeEngineIfNeeded {
    if (_engineStarted) {
        self.metalView.paused = (_pausedBySystem || _pausedByUser);
        return;
    }

    CAMetalLayer* metalLayer = nil;
    if ([_metalView.layer isKindOfClass:[CAMetalLayer class]]) {
        metalLayer = (CAMetalLayer*)_metalView.layer;
    }

    CGSize drawableSize = _metalView.drawableSize;
    int width = (int)(drawableSize.width > 0 ? drawableSize.width : self.view.bounds.size.width * [UIScreen mainScreen].scale);
    int height = (int)(drawableSize.height > 0 ? drawableSize.height : self.view.bounds.size.height * [UIScreen mainScreen].scale);

    _engine = std::make_unique<mbaa_recomp::RuntimeEngine>();
    std::string assetsUtf8 = _resolvedAssetsDir ? _resolvedAssetsDir.UTF8String : "";

    if (!_engine->init(assetsUtf8, (__bridge void*)metalLayer, width, height)) {
        std::string errMsg = _engine->last_error();
        _assetsReady = NO;
        _onboardingView.hidden = NO;
        _touchOverlay.hidden = YES;
        _onboardingStatusLabel.text = [NSString stringWithFormat:
            @"Lỗi khởi tạo RuntimeEngine / Failed to initialize RuntimeEngine from:\n%@\n\nDetail: %s",
            _resolvedAssetsDir,
            errMsg.empty() ? "unknown error" : errMsg.c_str()];
        _engine.reset();
        return;
    }

    _engineStarted = YES;
    _metalView.paused = (_pausedBySystem || _pausedByUser);
    [self startNetplayRefreshTimer];
    [self updateViewportAndOverlayLayout];
}

- (void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size {
    (void)view;
    if (_engine && _engineStarted && size.width >= 1.0 && size.height >= 1.0) {
        _engine->resize_drawable((int)size.width, (int)size.height);
    }
    [self updateViewportAndOverlayLayout];
}

- (void)drawInMTKView:(MTKView*)view {
    (void)view;
    if (!_assetsReady || !_engineStarted || !_engine || _pausedBySystem || _pausedByUser) {
        return;
    }
    _engine->step_frame();
}

#pragma mark - TouchOverlayViewDelegate

- (void)touchOverlayView:(TouchOverlayView*)overlay didUpdatePadState:(MBAAVirtualPadState)state {
    (void)overlay;
    if (!_engine || !_engineStarted) {
        return;
    }
    static_assert(MBAAVirtualButtonUp    == mbaa_recomp::kTouchUp,    "TouchButton Up mismatch");
    static_assert(MBAAVirtualButtonDown  == mbaa_recomp::kTouchDown,  "TouchButton Down mismatch");
    static_assert(MBAAVirtualButtonLeft  == mbaa_recomp::kTouchLeft,  "TouchButton Left mismatch");
    static_assert(MBAAVirtualButtonRight == mbaa_recomp::kTouchRight, "TouchButton Right mismatch");
    static_assert(MBAAVirtualButtonA     == mbaa_recomp::kTouchA,     "TouchButton A mismatch");
    static_assert(MBAAVirtualButtonB     == mbaa_recomp::kTouchB,     "TouchButton B mismatch");
    static_assert(MBAAVirtualButtonC     == mbaa_recomp::kTouchC,     "TouchButton C mismatch");
    static_assert(MBAAVirtualButtonD     == mbaa_recomp::kTouchD,     "TouchButton D mismatch");
    static_assert(MBAAVirtualButtonE     == mbaa_recomp::kTouchE,     "TouchButton E mismatch");
    static_assert(MBAAVirtualButtonStart == mbaa_recomp::kTouchStart, "TouchButton Start mismatch");
    static_assert(MBAAVirtualButtonCoin  == mbaa_recomp::kTouchCoin,  "TouchButton Coin mismatch");
    static_assert(MBAAVirtualButtonFN1   == mbaa_recomp::kTouchFN1,   "TouchButton FN1 mismatch");
    static_assert(MBAAVirtualButtonFN2   == mbaa_recomp::kTouchFN2,   "TouchButton FN2 mismatch");
    static_assert(MBAAVirtualButtonPause == mbaa_recomp::kTouchPause, "TouchButton Pause mismatch");
    static_assert(MBAAVirtualButtonDash  == mbaa_recomp::kTouchDash,  "TouchButton Dash mismatch");
    static_assert(MBAAVirtualButtonHeat  == mbaa_recomp::kTouchHeat,  "TouchButton Heat mismatch");

    mbaa_recomp::TouchInputState touchState{};
    touchState.buttons   = state.buttons;
    touchState.stick_x   = state.dpadX;
    touchState.stick_y   = state.dpadY;
    touchState.any_touch = (state.buttons != 0) || (state.dpadX != 0.0f) || (state.dpadY != 0.0f);
    _engine->set_touch_state(touchState);
}

- (void)touchOverlayViewDidTogglePause:(TouchOverlayView*)overlay {
    (void)overlay;
    _pausedByUser = !_pausedByUser;
    if (_pausedByUser) {
        [self refreshPauseDebugSummary];
    }
    _pauseOverlayView.hidden = !_pausedByUser;
    self.metalView.paused = (_pausedBySystem || _pausedByUser || !_assetsReady);
}

@end
