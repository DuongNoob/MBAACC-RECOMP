#import "GameViewController.h"
#import "TouchOverlayView.h"

#import <GameController/GameController.h>
#import <Metal/Metal.h>
#import <QuartzCore/CAMetalLayer.h>

#include "mbaa_recomp/hle_input.h"
#include "mbaa_recomp/runtime_engine.h"

#include <memory>
#include <string>

@interface GameViewController () <TouchOverlayViewDelegate>

@property (nonatomic, strong) MTKView* metalView;
@property (nonatomic, strong) TouchOverlayView* touchOverlay;
@property (nonatomic, strong) UIView* onboardingView;
@property (nonatomic, strong) UILabel* onboardingStatusLabel;
@property (nonatomic, strong) UIView* pauseOverlayView;
@property (nonatomic, strong) UITextView* pauseDebugTextView;
@property (nonatomic, strong) UIButton* copyDebugButton;

@property (nonatomic, assign) BOOL assetsReady;
@property (nonatomic, assign) BOOL engineStarted;
@property (nonatomic, assign) BOOL pausedBySystem;
@property (nonatomic, assign) BOOL pausedByUser;
@property (nonatomic, copy) NSString* resolvedAssetsDir;

@end

@implementation GameViewController {
    std::unique_ptr<mbaa_recomp::RuntimeEngine> _engine;
}

#pragma mark - Lifecycle & iOS Hardware Policy (iPhone SE 2020)

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor blackColor];

    [self setupMetalView];
    [self setupTouchOverlay];
    [self setupPauseOverlay];
    [self setupOnboardingView];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleAppBecameActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];

    [self checkBYOCAssetsAndBootIfReady];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
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
    if (_engine && _engineStarted) {
        _engine->shutdown();
        _engineStarted = NO;
    }
    _engine.reset();
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
    [_pauseDebugTextView.heightAnchor constraintEqualToConstant:125.0].active = YES;
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

    _copyDebugButton = [UIButton buttonWithType:UIButtonTypeSystem];
    UIButtonConfiguration* copyCfg = [UIButtonConfiguration filledButtonConfiguration];
    copyCfg.title = @"Copy Debug Log / Chép Log";
    copyCfg.baseBackgroundColor = [UIColor colorWithRed:0.16 green:0.46 blue:0.32 alpha:1.0];
    copyCfg.baseForegroundColor = [UIColor whiteColor];
    copyCfg.cornerStyle = UIButtonConfigurationCornerStyleMedium;
    copyCfg.contentInsets = NSDirectionalEdgeInsetsMake(8, 14, 8, 14);
    _copyDebugButton.configuration = copyCfg;
    [_copyDebugButton addTarget:self action:@selector(onCopyDebugLogTapped) forControlEvents:UIControlEventTouchUpInside];
    [card addArrangedSubview:_copyDebugButton];

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
    UIButtonConfiguration* cfg = _copyDebugButton.configuration;
    cfg.title = @"Copied! / Đã chép";
    _copyDebugButton.configuration = cfg;
    __weak GameViewController* weakSelf = self;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        GameViewController* strongSelf = weakSelf;
        if (!strongSelf) return;
        UIButtonConfiguration* restore = strongSelf.copyDebugButton.configuration;
        restore.title = @"Copy Debug Log / Chép Log";
        strongSelf.copyDebugButton.configuration = restore;
    });
}

- (void)onResumeTapped {
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
    [self updateViewportAndOverlayLayout];
}

- (void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size {
    (void)view;
    (void)size;
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
