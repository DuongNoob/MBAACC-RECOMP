#import "TouchOverlayView.h"
#import <GameController/GameController.h>
#include <math.h>

typedef NS_ENUM(NSInteger, MBAATouchControlTag) {
    MBAATouchControlDPad = 0,
    MBAATouchControlBtnA,
    MBAATouchControlBtnB,
    MBAATouchControlBtnC,
    MBAATouchControlBtnD,
    MBAATouchControlBtnE,
    MBAATouchControlDashMacro,   // A + B
    MBAATouchControlHeatMacro,   // A + B + C
    MBAATouchControlStart,
    MBAATouchControlCoin,
    MBAATouchControlFN1,
    MBAATouchControlFN2,
    MBAATouchControlPause,
    MBAATouchControlCount
};

@interface MBAAVirtualControlZone : NSObject
@property (nonatomic, assign) MBAATouchControlTag tag;
@property (nonatomic, assign) CGRect frame;
@property (nonatomic, assign) BOOL isRound;
@property (nonatomic, copy) NSString* title;
@property (nonatomic, strong) UIColor* tintColor;
@property (nonatomic, strong) UIView* containerView;
@property (nonatomic, strong) UILabel* labelView;
@property (nonatomic, assign) BOOL pressed;
@end

@implementation MBAAVirtualControlZone
@end

@interface TouchOverlayView ()
@property (nonatomic, strong) UIView* controlsContainer;
@property (nonatomic, strong) UIView* dpadBaseView;
@property (nonatomic, strong) UIView* dpadKnobView;
@property (nonatomic, strong) CAShapeLayer* dpadHighlightLayer;
@property (nonatomic, strong) NSMutableArray<MBAAVirtualControlZone*>* buttonZones;
@property (nonatomic, strong) NSMapTable<UITouch*, NSNumber*>* activeTouches;
@property (nonatomic, weak, nullable) UITouch* dpadTouch;
@property (nonatomic, assign) CGRect dpadFrame;
@property (nonatomic, assign) CGRect dpadHitRect;
@property (nonatomic, assign) CGFloat dpadX;
@property (nonatomic, assign) CGFloat dpadY;
@property (nonatomic, assign) uint32_t dpadMask;

// Opacity & HUD toggle panel
@property (nonatomic, strong) UIButton* hudSettingsButton;
@property (nonatomic, strong) UIView* settingsPopover;
@property (nonatomic, strong) UISlider* opacitySlider;
@property (nonatomic, strong) UISwitch* hideControlsSwitch;
@property (nonatomic, strong) UILabel* controllerBadgeLabel;
@property (nonatomic, assign) CGRect cachedViewportRect;
@property (nonatomic, assign, readwrite) MBAAVirtualPadState currentState;
@property (nonatomic, assign, readwrite, getter=isControllerConnected) BOOL controllerConnected;
@end

static NSString* const kUserOpacityDefaultsKey = @"MBAACC.TouchOverlay.Opacity";
static NSString* const kManualHiddenDefaultsKey = @"MBAACC.TouchOverlay.ManualHidden";

@implementation TouchOverlayView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.multipleTouchEnabled = YES;
        self.exclusiveTouch = NO;

        NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
        NSNumber* savedOpacity = [defaults objectForKey:kUserOpacityDefaultsKey];
        _userOpacity = savedOpacity ? MIN(1.0, MAX(0.15, savedOpacity.doubleValue)) : 0.72;
        _manualHidden = [defaults boolForKey:kManualHiddenDefaultsKey];
        _cachedViewportRect = CGRectZero;

        _activeTouches = [NSMapTable weakToStrongObjectsMapTable];
        _buttonZones = [NSMutableArray array];

        [self setupUI];
        [self registerGameControllerNotifications];
        [self refreshControllerConnectionAnimated:NO];
    }
    return self;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

#pragma mark - UI Construction

- (void)setupUI {
    _controlsContainer = [[UIView alloc] initWithFrame:self.bounds];
    _controlsContainer.backgroundColor = [UIColor clearColor];
    _controlsContainer.userInteractionEnabled = NO;
    [self addSubview:_controlsContainer];

    // 8-way Virtual D-Pad
    _dpadBaseView = [[UIView alloc] initWithFrame:CGRectZero];
    _dpadBaseView.backgroundColor = [UIColor colorWithWhite:0.08 alpha:0.62];
    _dpadBaseView.layer.borderColor = [UIColor colorWithWhite:0.90 alpha:0.42].CGColor;
    _dpadBaseView.layer.borderWidth = 1.5;
    _dpadBaseView.userInteractionEnabled = NO;
    [_controlsContainer addSubview:_dpadBaseView];

    _dpadHighlightLayer = [CAShapeLayer layer];
    _dpadHighlightLayer.fillColor = [UIColor colorWithRed:0.35 green:0.72 blue:1.0 alpha:0.45].CGColor;
    [_dpadBaseView.layer addSublayer:_dpadHighlightLayer];

    _dpadKnobView = [[UIView alloc] initWithFrame:CGRectZero];
    _dpadKnobView.backgroundColor = [UIColor colorWithWhite:0.95 alpha:0.38];
    _dpadKnobView.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.75].CGColor;
    _dpadKnobView.layer.borderWidth = 1.5;
    _dpadKnobView.userInteractionEnabled = NO;
    [_dpadBaseView addSubview:_dpadKnobView];

    // Attack buttons & fighting-game macros (right side) + utility pills (left side)
    [self addButtonZone:MBAATouchControlBtnA title:@"A" round:YES color:[UIColor colorWithRed:0.25 green:0.65 blue:1.0 alpha:1.0]];
    [self addButtonZone:MBAATouchControlBtnB title:@"B" round:YES color:[UIColor colorWithRed:0.28 green:0.85 blue:0.48 alpha:1.0]];
    [self addButtonZone:MBAATouchControlBtnC title:@"C" round:YES color:[UIColor colorWithRed:1.0 green:0.42 blue:0.35 alpha:1.0]];
    [self addButtonZone:MBAATouchControlBtnD title:@"D" round:YES color:[UIColor colorWithRed:0.98 green:0.78 blue:0.25 alpha:1.0]];
    [self addButtonZone:MBAATouchControlBtnE title:@"E" round:YES color:[UIColor colorWithRed:0.78 green:0.45 blue:1.0 alpha:1.0]];
    [self addButtonZone:MBAATouchControlDashMacro title:@"DASH\nA+B" round:NO color:[UIColor colorWithRed:0.20 green:0.80 blue:0.95 alpha:1.0]];
    [self addButtonZone:MBAATouchControlHeatMacro title:@"HEAT\nA+B+C" round:NO color:[UIColor colorWithRed:1.0 green:0.55 blue:0.18 alpha:1.0]];

    [self addButtonZone:MBAATouchControlStart title:@"START" round:NO color:[UIColor colorWithWhite:0.85 alpha:1.0]];
    [self addButtonZone:MBAATouchControlCoin title:@"COIN" round:NO color:[UIColor colorWithWhite:0.75 alpha:1.0]];
    [self addButtonZone:MBAATouchControlPause title:@"PAUSE" round:NO color:[UIColor colorWithWhite:0.92 alpha:1.0]];
    [self addButtonZone:MBAATouchControlFN1 title:@"FN1" round:NO color:[UIColor colorWithRed:0.65 green:0.75 blue:0.90 alpha:1.0]];
    [self addButtonZone:MBAATouchControlFN2 title:@"FN2" round:NO color:[UIColor colorWithRed:0.65 green:0.75 blue:0.90 alpha:1.0]];

    // Discrete HUD settings button (always tappable at low opacity even when controller connected)
    _hudSettingsButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [_hudSettingsButton setTitle:@"PAD" forState:UIControlStateNormal];
    _hudSettingsButton.titleLabel.font = [UIFont monospacedSystemFontOfSize:10.0 weight:UIFontWeightBold];
    [_hudSettingsButton setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    _hudSettingsButton.backgroundColor = [UIColor colorWithWhite:0.12 alpha:0.65];
    _hudSettingsButton.layer.cornerRadius = 8.0;
    _hudSettingsButton.layer.borderWidth = 1.0;
    _hudSettingsButton.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.30].CGColor;
    [_hudSettingsButton addTarget:self action:@selector(toggleSettingsPopover) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:_hudSettingsButton];

    // Controller auto-fade indicator badge
    _controllerBadgeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _controllerBadgeLabel.font = [UIFont systemFontOfSize:10.0 weight:UIFontWeightSemibold];
    _controllerBadgeLabel.textColor = [UIColor colorWithRed:0.55 green:0.95 blue:0.65 alpha:1.0];
    _controllerBadgeLabel.backgroundColor = [UIColor colorWithWhite:0.08 alpha:0.75];
    _controllerBadgeLabel.textAlignment = NSTextAlignmentCenter;
    _controllerBadgeLabel.layer.cornerRadius = 6.0;
    _controllerBadgeLabel.layer.masksToBounds = YES;
    _controllerBadgeLabel.text = @"GCController Active";
    _controllerBadgeLabel.alpha = 0.0;
    [self addSubview:_controllerBadgeLabel];

    [self setupSettingsPopover];
}

- (void)setupSettingsPopover {
    _settingsPopover = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 236, 126)];
    _settingsPopover.backgroundColor = [UIColor colorWithWhite:0.08 alpha:0.92];
    _settingsPopover.layer.cornerRadius = 12.0;
    _settingsPopover.layer.borderWidth = 1.0;
    _settingsPopover.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.25].CGColor;
    _settingsPopover.hidden = YES;

    UILabel* opacityLabel = [[UILabel alloc] initWithFrame:CGRectMake(14, 12, 208, 18)];
    opacityLabel.text = @"Touch Opacity";
    opacityLabel.font = [UIFont systemFontOfSize:12.0 weight:UIFontWeightSemibold];
    opacityLabel.textColor = [UIColor whiteColor];
    [_settingsPopover addSubview:opacityLabel];

    _opacitySlider = [[UISlider alloc] initWithFrame:CGRectMake(14, 34, 208, 28)];
    _opacitySlider.minimumValue = 0.15f;
    _opacitySlider.maximumValue = 1.0f;
    _opacitySlider.value = (float)_userOpacity;
    [_opacitySlider addTarget:self action:@selector(opacitySliderChanged:) forControlEvents:UIControlEventValueChanged];
    [_settingsPopover addSubview:_opacitySlider];

    UILabel* hideLabel = [[UILabel alloc] initWithFrame:CGRectMake(14, 78, 140, 24)];
    hideLabel.text = @"Hide Virtual Pad";
    hideLabel.font = [UIFont systemFontOfSize:12.0 weight:UIFontWeightMedium];
    hideLabel.textColor = [UIColor colorWithWhite:0.9 alpha:1.0];
    [_settingsPopover addSubview:hideLabel];

    _hideControlsSwitch = [[UISwitch alloc] initWithFrame:CGRectMake(166, 74, 51, 31)];
    _hideControlsSwitch.on = _manualHidden;
    [_hideControlsSwitch addTarget:self action:@selector(hideSwitchChanged:) forControlEvents:UIControlEventValueChanged];
    [_settingsPopover addSubview:_hideControlsSwitch];

    [self addSubview:_settingsPopover];
}

- (void)addButtonZone:(MBAATouchControlTag)tag title:(NSString*)title round:(BOOL)isRound color:(UIColor*)color {
    MBAAVirtualControlZone* zone = [[MBAAVirtualControlZone alloc] init];
    zone.tag = tag;
    zone.title = title;
    zone.isRound = isRound;
    zone.tintColor = color;

    UIView* container = [[UIView alloc] initWithFrame:CGRectZero];
    container.backgroundColor = [color colorWithAlphaComponent:0.18];
    container.layer.borderColor = [color colorWithAlphaComponent:0.72].CGColor;
    container.layer.borderWidth = 1.5;
    container.userInteractionEnabled = NO;

    UILabel* label = [[UILabel alloc] initWithFrame:CGRectZero];
    label.text = title;
    label.textAlignment = NSTextAlignmentCenter;
    label.numberOfLines = 2;
    label.textColor = [UIColor whiteColor];
    label.font = [UIFont systemFontOfSize:(isRound ? 15.0 : 10.0) weight:UIFontWeightBold];
    label.adjustsFontSizeToFitWidth = YES;
    label.minimumScaleFactor = 0.65;
    label.userInteractionEnabled = NO;
    [container addSubview:label];

    zone.containerView = container;
    zone.labelView = label;
    [_controlsContainer addSubview:container];
    [_buttonZones addObject:zone];
}

#pragma mark - Layout (Tuned for iPhone SE 2020: 1334x750 / 667x375 pt)

- (void)layoutSubviews {
    [super layoutSubviews];
    _controlsContainer.frame = self.bounds;
    if (CGRectIsEmpty(_cachedViewportRect)) {
        CGFloat w = self.bounds.size.width;
        CGFloat h = self.bounds.size.height;
        CGFloat vpW = MIN(w, h * (4.0 / 3.0));
        CGFloat vpH = vpW * (3.0 / 4.0);
        CGRect defaultVP = CGRectMake((w - vpW) * 0.5, (h - vpH) * 0.5, vpW, vpH);
        [self updateLayoutForViewportRect:defaultVP];
    } else {
        [self updateLayoutForViewportRect:_cachedViewportRect];
    }
}

- (void)updateLayoutForViewportRect:(CGRect)viewportRect {
    _cachedViewportRect = viewportRect;

    CGFloat w = self.bounds.size.width;
    CGFloat h = self.bounds.size.height;
    if (w <= 0 || h <= 0) {
        return;
    }

    UIEdgeInsets safe = UIEdgeInsetsZero;
    if (@available(iOS 11.0, *)) {
        safe = self.safeAreaInsets;
    }

    // On iPhone SE 2020 (667x375 pt): viewportRect.origin.x == 83.5 pt (167 px) each side.
    // On notched iPhones: clamp inward modestly if sidebar is narrower than 96 pt.
    CGFloat leftSidebarWidth = MAX(safe.left + 84.0, CGRectGetMinX(viewportRect));
    CGFloat rightSidebarLeft = MIN(w - safe.right - 84.0, CGRectGetMaxX(viewportRect));
    CGFloat rightSidebarWidth = w - safe.right - rightSidebarLeft;
    CGFloat leftAnchor = safe.left + 6.0;
    CGFloat rightAnchor = w - safe.right - 6.0;

    // Left top utilities: START, COIN, PAUSE
    CGFloat utilW = MIN(72.0, MAX(54.0, leftSidebarWidth - safe.left - 12.0));
    CGFloat utilH = 26.0;
    [self setFrame:CGRectMake(leftAnchor, 10.0, utilW, utilH) forTag:MBAATouchControlPause];
    [self setFrame:CGRectMake(leftAnchor, 42.0, utilW, utilH) forTag:MBAATouchControlStart];
    [self setFrame:CGRectMake(leftAnchor, 74.0, utilW, utilH) forTag:MBAATouchControlCoin];

    // Left bottom 8-way D-Pad (116x116 pt on SE 2020 so it hugs the 83.5 pt sidebar cleanly)
    CGFloat dpadSize = MIN(116.0, MAX(96.0, h * 0.31));
    CGFloat dpadCenterX = MAX(leftAnchor + dpadSize * 0.5, (safe.left + leftSidebarWidth) * 0.62);
    CGFloat dpadCenterY = h - 14.0 - dpadSize * 0.5;
    _dpadFrame = CGRectMake(dpadCenterX - dpadSize * 0.5, dpadCenterY - dpadSize * 0.5, dpadSize, dpadSize);
    _dpadHitRect = CGRectInset(_dpadFrame, -20.0, -20.0);
    _dpadBaseView.frame = _dpadFrame;
    _dpadBaseView.layer.cornerRadius = dpadSize * 0.5;
    _dpadHighlightLayer.frame = _dpadBaseView.bounds;

    CGFloat knobSize = dpadSize * 0.36;
    _dpadKnobView.bounds = CGRectMake(0, 0, knobSize, knobSize);
    _dpadKnobView.layer.cornerRadius = knobSize * 0.5;
    [self updateDPadVisuals];

    // Right top utilities: PAD (HUD toggle), FN1, FN2
    CGFloat smallW = 42.0;
    CGFloat smallH = 24.0;
    _hudSettingsButton.frame = CGRectMake(rightAnchor - smallW, 10.0, smallW, smallH);
    [self setFrame:CGRectMake(rightAnchor - smallW * 2.0 - 6.0, 10.0, smallW, smallH) forTag:MBAATouchControlFN1];
    [self setFrame:CGRectMake(rightAnchor - smallW, 40.0, smallW, smallH) forTag:MBAATouchControlFN2];

    _controllerBadgeLabel.frame = CGRectMake(CGRectGetMidX(viewportRect) - 72.0, 10.0, 144.0, 22.0);
    _settingsPopover.frame = CGRectMake(rightAnchor - 236.0, 40.0, 236.0, 126.0);

    // Right thumb fighting-game cluster (A/B/C/D/E + Dash A+B + Heat A+B+C),
    // strictly anchored inward from rightAnchor so zero controls clip off 667x375 pt bounds.
    CGFloat btnR = MIN(46.0, MAX(40.0, (rightSidebarWidth + 28.0) * 0.40));
    CGFloat gap = 6.0;
    CGFloat macroW = 58.0;
    CGFloat macroH = 32.0;
    CGFloat macroY = h - 8.0 - macroH;

    [self setFrame:CGRectMake(rightAnchor - macroW, macroY, macroW, macroH) forTag:MBAATouchControlDashMacro];
    [self setFrame:CGRectMake(rightAnchor - macroW * 2.0 - gap, macroY, macroW, macroH) forTag:MBAATouchControlHeatMacro];

    CGFloat col3X = rightAnchor - btnR;
    CGFloat col2X = col3X - (btnR + gap);
    CGFloat col1X = col2X - (btnR + gap);
    CGFloat lowerRowBaseY = macroY - 8.0 - btnR;
    CGFloat upperRowBaseY = lowerRowBaseY - (btnR + 10.0);

    [self setFrame:CGRectMake(col1X, upperRowBaseY + 20.0, btnR, btnR) forTag:MBAATouchControlBtnA];
    [self setFrame:CGRectMake(col2X, upperRowBaseY + 10.0, btnR, btnR) forTag:MBAATouchControlBtnB];
    [self setFrame:CGRectMake(col3X, upperRowBaseY,        btnR, btnR) forTag:MBAATouchControlBtnC];
    [self setFrame:CGRectMake(col2X, lowerRowBaseY,        btnR, btnR) forTag:MBAATouchControlBtnD];
    [self setFrame:CGRectMake(col3X, lowerRowBaseY - 10.0, btnR, btnR) forTag:MBAATouchControlBtnE];
}

- (void)setFrame:(CGRect)frame forTag:(MBAATouchControlTag)tag {
    for (MBAAVirtualControlZone* zone in _buttonZones) {
        if (zone.tag == tag) {
            zone.frame = frame;
            zone.containerView.frame = frame;
            zone.containerView.layer.cornerRadius = zone.isRound ? (MIN(frame.size.width, frame.size.height) * 0.5) : 8.0;
            zone.labelView.frame = CGRectInset(zone.containerView.bounds, 3.0, 2.0);
            break;
        }
    }
}

#pragma mark - GCController Auto-Fade & Opacity Controls

- (void)registerGameControllerNotifications {
    NSNotificationCenter* nc = [NSNotificationCenter defaultCenter];
    [nc addObserver:self selector:@selector(onControllerChanged:) name:GCControllerDidConnectNotification object:nil];
    [nc addObserver:self selector:@selector(onControllerChanged:) name:GCControllerDidDisconnectNotification object:nil];
}

- (void)onControllerChanged:(NSNotification*)note {
    (void)note;
    [self refreshControllerConnectionAnimated:YES];
}

- (void)refreshControllerConnectionAnimated:(BOOL)animated {
    BOOL connected = [GCController controllers].count > 0;
    _controllerConnected = connected;
    [self applyEffectiveOpacityAnimated:animated];

    if (connected) {
        _controllerBadgeLabel.alpha = 1.0;
        [UIView animateWithDuration:0.5 delay:2.0 options:UIViewAnimationOptionBeginFromCurrentState animations:^{
            self->_controllerBadgeLabel.alpha = 0.0;
        } completion:nil];
    }
}

- (void)setUserOpacity:(CGFloat)userOpacity {
    _userOpacity = MIN(1.0, MAX(0.15, userOpacity));
    [[NSUserDefaults standardUserDefaults] setDouble:_userOpacity forKey:kUserOpacityDefaultsKey];
    [self applyEffectiveOpacityAnimated:NO];
}

- (void)setManualHidden:(BOOL)manualHidden {
    _manualHidden = manualHidden;
    [[NSUserDefaults standardUserDefaults] setBool:_manualHidden forKey:kManualHiddenDefaultsKey];
    [self applyEffectiveOpacityAnimated:YES];
}

- (void)applyEffectiveOpacityAnimated:(BOOL)animated {
    CGFloat targetAlpha = (_manualHidden || _controllerConnected) ? 0.0 : _userOpacity;
    CGFloat padBtnAlpha = (_manualHidden || _controllerConnected) ? 0.28 : 0.85;
    void (^apply)(void) = ^{
        self->_controlsContainer.alpha = targetAlpha;
        self->_hudSettingsButton.alpha = padBtnAlpha;
    };
    if (animated) {
        [UIView animateWithDuration:0.25 animations:apply];
    } else {
        apply();
    }
}

- (void)toggleSettingsPopover {
    _settingsPopover.hidden = !_settingsPopover.hidden;
}

- (void)opacitySliderChanged:(UISlider*)slider {
    self.userOpacity = slider.value;
}

- (void)hideSwitchChanged:(UISwitch*)sender {
    self.manualHidden = sender.isOn;
}

#pragma mark - Multi-Touch Hit Testing & 8-Way D-Pad

- (UIView*)hitTest:(CGPoint)point withEvent:(UIEvent*)event {
    // Allow interactive controls inside popover & HUD toggle button to handle taps normally.
    if (!_settingsPopover.hidden) {
        CGPoint popPt = [self convertPoint:point toView:_settingsPopover];
        UIView* sub = [_settingsPopover hitTest:popPt withEvent:event];
        if (sub) {
            return sub;
        }
    }
    CGPoint hudPt = [self convertPoint:point toView:_hudSettingsButton];
    if ([_hudSettingsButton pointInside:hudPt withEvent:event]) {
        return _hudSettingsButton;
    }

    // Only intercept touches on actual virtual control zones; pass center gameplay taps through cleanly.
    if ([self controlZoneAtPoint:point] != nil || (!_manualHidden && !_controllerConnected && CGRectContainsPoint(_dpadHitRect, point))) {
        return self;
    }
    return nil;
}

- (nullable MBAAVirtualControlZone*)controlZoneAtPoint:(CGPoint)point {
    if (_manualHidden || _controllerConnected) {
        return nil;
    }
    for (MBAAVirtualControlZone* zone in _buttonZones) {
        CGRect hitFrame = CGRectInset(zone.frame, -6.0, -6.0);
        if (CGRectContainsPoint(hitFrame, point)) {
            return zone;
        }
    }
    return nil;
}

- (void)touchesBegan:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
    (void)event;
    if (!_settingsPopover.hidden) {
        _settingsPopover.hidden = YES;
    }

    for (UITouch* touch in touches) {
        CGPoint pt = [touch locationInView:self];
        if (_dpadTouch == nil && !_manualHidden && !_controllerConnected && CGRectContainsPoint(_dpadHitRect, pt)) {
            _dpadTouch = touch;
            [_activeTouches setObject:@(MBAATouchControlDPad) forKey:touch];
            [self updateDPadWithPoint:pt];
            continue;
        }

        MBAAVirtualControlZone* zone = [self controlZoneAtPoint:pt];
        if (zone != nil) {
            if (zone.tag == MBAATouchControlPause) {
                if ([self.delegate respondsToSelector:@selector(touchOverlayViewDidTogglePause:)]) {
                    [self.delegate touchOverlayViewDidTogglePause:self];
                }
            }
            [_activeTouches setObject:@(zone.tag) forKey:touch];
        }
    }
    [self recomputeButtonStates];
}

- (void)touchesMoved:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
    (void)event;
    for (UITouch* touch in touches) {
        CGPoint pt = [touch locationInView:self];
        if (touch == _dpadTouch) {
            [self updateDPadWithPoint:pt];
        } else {
            // Allow smooth thumb slide between A/B/C/D/E/macros on right hand
            MBAAVirtualControlZone* zone = [self controlZoneAtPoint:pt];
            if (zone != nil && zone.tag != MBAATouchControlPause) {
                [_activeTouches setObject:@(zone.tag) forKey:touch];
            } else if ([_activeTouches objectForKey:touch] != nil) {
                [_activeTouches removeObjectForKey:touch];
            }
        }
    }
    [self recomputeButtonStates];
}

- (void)touchesEnded:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
    (void)event;
    for (UITouch* touch in touches) {
        if (touch == _dpadTouch) {
            _dpadTouch = nil;
            [self resetDPad];
        }
        [_activeTouches removeObjectForKey:touch];
    }
    [self recomputeButtonStates];
}

- (void)touchesCancelled:(NSSet<UITouch*>*)touches withEvent:(UIEvent*)event {
    [self touchesEnded:touches withEvent:event];
}

- (void)updateDPadWithPoint:(CGPoint)point {
    CGPoint center = CGPointMake(CGRectGetMidX(_dpadFrame), CGRectGetMidY(_dpadFrame));
    CGFloat radius = _dpadFrame.size.width * 0.5;
    CGFloat dx = point.x - center.x;
    CGFloat dy = center.y - point.y;  // +Y = Up
    CGFloat dist = hypot(dx, dy);

    CGFloat deadzone = radius * 0.20;
    if (dist < deadzone) {
        _dpadX = 0.0;
        _dpadY = 0.0;
        _dpadMask = 0;
        [self updateDPadVisuals];
        return;
    }

    CGFloat clamped = MIN(dist, radius);
    CGFloat nx = (dx / dist) * (clamped / radius);
    CGFloat ny = (dy / dist) * (clamped / radius);
    _dpadX = nx;
    _dpadY = ny;

    // 8-way sectorization (22.5 deg boundaries -> 8 equal 45 deg wedges)
    double angleDeg = atan2(dy, dx) * (180.0 / M_PI);  // -180..+180
    if (angleDeg < 0.0) angleDeg += 360.0;
    int sector = ((int)floor((angleDeg + 22.5) / 45.0)) % 8;

    static const uint32_t kSectorMasks[8] = {
        MBAAVirtualButtonRight,                         // 0: E
        MBAAVirtualButtonRight | MBAAVirtualButtonUp,   // 1: NE
        MBAAVirtualButtonUp,                            // 2: N
        MBAAVirtualButtonLeft  | MBAAVirtualButtonUp,   // 3: NW
        MBAAVirtualButtonLeft,                          // 4: W
        MBAAVirtualButtonLeft  | MBAAVirtualButtonDown, // 5: SW
        MBAAVirtualButtonDown,                          // 6: S
        MBAAVirtualButtonRight | MBAAVirtualButtonDown, // 7: SE
    };
    _dpadMask = kSectorMasks[sector];
    [self updateDPadVisuals];
}

- (void)resetDPad {
    _dpadX = 0.0;
    _dpadY = 0.0;
    _dpadMask = 0;
    [self updateDPadVisuals];
}

- (void)updateDPadVisuals {
    CGFloat radius = _dpadBaseView.bounds.size.width * 0.5;
    CGFloat travel = radius * 0.58;
    _dpadKnobView.center = CGPointMake(radius + _dpadX * travel, radius - _dpadY * travel);

    if (_dpadMask == 0 || radius <= 0.0) {
        _dpadHighlightLayer.path = nil;
        return;
    }

    // Highlight active sector wedge
    CGFloat angle = atan2(-_dpadY, _dpadX);
    UIBezierPath* wedge = [UIBezierPath bezierPath];
    [wedge moveToPoint:CGPointMake(radius, radius)];
    [wedge addArcWithCenter:CGPointMake(radius, radius)
                     radius:radius - 2.0
                 startAngle:angle - (M_PI / 8.0)
                   endAngle:angle + (M_PI / 8.0)
                  clockwise:YES];
    [wedge closePath];
    _dpadHighlightLayer.path = wedge.CGPath;
}

- (void)recomputeButtonStates {
    for (MBAAVirtualControlZone* zone in _buttonZones) {
        zone.pressed = NO;
    }

    NSEnumerator<NSNumber*>* values = [_activeTouches objectEnumerator];
    for (NSNumber* tagNum in values) {
        MBAATouchControlTag tag = (MBAATouchControlTag)tagNum.integerValue;
        for (MBAAVirtualControlZone* zone in _buttonZones) {
            if (zone.tag == tag) {
                zone.pressed = YES;
            }
        }
    }

    uint32_t mask = _dpadMask;
    for (MBAAVirtualControlZone* zone in _buttonZones) {
        BOOL active = zone.pressed;
        zone.containerView.backgroundColor = [zone.tintColor colorWithAlphaComponent:(active ? 0.55 : 0.18)];
        zone.containerView.transform = active ? CGAffineTransformMakeScale(0.94, 0.94) : CGAffineTransformIdentity;

        if (!active) continue;
        switch (zone.tag) {
            case MBAATouchControlBtnA: mask |= MBAAVirtualButtonA; break;
            case MBAATouchControlBtnB: mask |= MBAAVirtualButtonB; break;
            case MBAATouchControlBtnC: mask |= MBAAVirtualButtonC; break;
            case MBAATouchControlBtnD: mask |= MBAAVirtualButtonD; break;
            case MBAATouchControlBtnE: mask |= MBAAVirtualButtonE; break;
            case MBAATouchControlDashMacro:
                mask |= (MBAAVirtualButtonDash | MBAAVirtualButtonA | MBAAVirtualButtonB);
                break;
            case MBAATouchControlHeatMacro:
                mask |= (MBAAVirtualButtonHeat | MBAAVirtualButtonA | MBAAVirtualButtonB | MBAAVirtualButtonC);
                break;
            case MBAATouchControlStart: mask |= MBAAVirtualButtonStart; break;
            case MBAATouchControlCoin:  mask |= MBAAVirtualButtonCoin; break;
            case MBAATouchControlFN1:   mask |= MBAAVirtualButtonFN1; break;
            case MBAATouchControlFN2:   mask |= MBAAVirtualButtonFN2; break;
            case MBAATouchControlPause: mask |= MBAAVirtualButtonPause; break;
            default: break;
        }
    }

    MBAAVirtualPadState state;
    state.buttons = mask;
    state.dpadX = (float)_dpadX;
    state.dpadY = (float)_dpadY;
    self.currentState = state;

    if ([self.delegate respondsToSelector:@selector(touchOverlayView:didUpdatePadState:)]) {
        [self.delegate touchOverlayView:self didUpdatePadState:state];
    }
}

@end
