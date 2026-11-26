#import "TouchOverlayView.h"
#import <GameController/GameController.h>
#import <QuartzCore/QuartzCore.h>
#include <math.h>

typedef NS_ENUM(NSInteger, MBAATouchControlTag) {
    MBAATouchControlDPad = 0,
    MBAATouchControlBtnA,        // PS2 Square (□)  -> A (Light / Punch / Confirm)
    MBAATouchControlBtnB,        // PS2 Cross (×)   -> B (Medium / Low Kick / Cancel)
    MBAATouchControlBtnC,        // PS2 Circle (○)  -> C (Heavy / High Kick)
    MBAATouchControlBtnD,        // PS2 Triangle (△)-> D (Shield / Magic)
    MBAATouchControlBtnE,        // PS2 R1          -> E (Quick Action)
    MBAATouchControlThrowMacro,  // PS2 L1          -> Throw / Evade macro (A + D)
    MBAATouchControlDashMacro,   // PS2 R2          -> Dash macro (A + B)
    MBAATouchControlHeatMacro,   // PS2 L2          -> Heat macro (A + B + C)
    MBAATouchControlStart,       // PS2 Start (▷)   -> Start / Pause game
    MBAATouchControlCoin,        // Reserved Coin / Select flag
    MBAATouchControlFN1,         // PS2 Select (▭)  -> FN1 (Training Reset)
    MBAATouchControlFN2,         // PS2 Double-Ring (◎) -> FN2 (Training Function 2)
    MBAATouchControlPause,       // Top-Right (||)  -> iOS Pause & Debug overlay toggle
    MBAATouchControlCount
};

typedef NS_ENUM(NSInteger, MBAAPS2VisualStyle) {
    MBAAPS2VisualStyleShoulderRect = 0,
    MBAAPS2VisualStyleFaceSquare,
    MBAAPS2VisualStyleFaceTriangle,
    MBAAPS2VisualStyleFaceCircle,
    MBAAPS2VisualStyleFaceCross,
    MBAAPS2VisualStyleSelectRect,
    MBAAPS2VisualStyleAnalogDoubleRing,
    MBAAPS2VisualStyleStartTriangle,
    MBAAPS2VisualStylePauseBars,
};

static const CGFloat kPS2StrokeWidth = 2.0;

@interface MBAAVirtualControlZone : NSObject
@property (nonatomic, assign) MBAATouchControlTag tag;
@property (nonatomic, assign) MBAAPS2VisualStyle visualStyle;
@property (nonatomic, assign) CGRect frame;
@property (nonatomic, assign) BOOL circularHit;
@property (nonatomic, assign) CGFloat hitPadding;
@property (nonatomic, strong, nullable) NSString* title;
@property (nonatomic, strong) UIView* containerView;
@property (nonatomic, strong) CAShapeLayer* outerLayer;
@property (nonatomic, strong, nullable) CAShapeLayer* symbolLayer;
@property (nonatomic, strong, nullable) UILabel* labelView;
@property (nonatomic, assign) BOOL pressed;
@end

@implementation MBAAVirtualControlZone
@end

@interface TouchOverlayView ()
@property (nonatomic, strong) UIView* controlsContainer;
@property (nonatomic, strong) UIView* dpadBaseView;
@property (nonatomic, strong) CAShapeLayer* dpadUpLayer;
@property (nonatomic, strong) CAShapeLayer* dpadDownLayer;
@property (nonatomic, strong) CAShapeLayer* dpadLeftLayer;
@property (nonatomic, strong) CAShapeLayer* dpadRightLayer;
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

static UIColor* ps2IdleStrokeColor(void) {
    return [UIColor colorWithWhite:1.0 alpha:0.88];
}

static UIColor* ps2PressedStrokeColor(void) {
    return [UIColor colorWithWhite:1.0 alpha:1.0];
}

static UIColor* ps2IdleFillColor(void) {
    return [UIColor colorWithWhite:0.0 alpha:0.22];
}

static UIColor* ps2PressedFillColor(void) {
    return [UIColor colorWithWhite:1.0 alpha:0.34];
}

@implementation TouchOverlayView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.multipleTouchEnabled = YES;
        self.exclusiveTouch = NO;

        NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
        NSNumber* savedOpacity = [defaults objectForKey:kUserOpacityDefaultsKey];
        _userOpacity = savedOpacity ? MIN(1.0, MAX(0.15, savedOpacity.doubleValue)) : 0.78;
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

#pragma mark - UI Construction (AetherSX2 PS2 Vector Style)

- (CGFloat)currentDisplayScale {
    CGFloat scale = self.traitCollection.displayScale;
    if (scale > 0.0) {
        return scale;
    }
    return (self.contentScaleFactor > 0.0) ? self.contentScaleFactor : 2.0;
}

- (CAShapeLayer*)makeVectorShapeLayer {
    CAShapeLayer* layer = [CAShapeLayer layer];
    layer.fillColor = ps2IdleFillColor().CGColor;
    layer.strokeColor = ps2IdleStrokeColor().CGColor;
    layer.lineWidth = kPS2StrokeWidth;
    layer.lineJoin = kCALineJoinMiter;
    layer.lineCap = kCALineCapButt;
    layer.contentsScale = [self currentDisplayScale];
    return layer;
}

- (void)setupUI {
    _controlsContainer = [[UIView alloc] initWithFrame:self.bounds];
    _controlsContainer.backgroundColor = [UIColor clearColor];
    _controlsContainer.userInteractionEnabled = NO;
    [self addSubview:_controlsContainer];

    // Bottom-Left: PS2 4-way D-Pad (4 inward-pointing arrow pentagons with 8-way touch)
    _dpadBaseView = [[UIView alloc] initWithFrame:CGRectZero];
    _dpadBaseView.backgroundColor = [UIColor clearColor];
    _dpadBaseView.userInteractionEnabled = NO;
    [_controlsContainer addSubview:_dpadBaseView];

    _dpadUpLayer = [self makeVectorShapeLayer];
    _dpadDownLayer = [self makeVectorShapeLayer];
    _dpadLeftLayer = [self makeVectorShapeLayer];
    _dpadRightLayer = [self makeVectorShapeLayer];
    [_dpadBaseView.layer addSublayer:_dpadUpLayer];
    [_dpadBaseView.layer addSublayer:_dpadDownLayer];
    [_dpadBaseView.layer addSublayer:_dpadLeftLayer];
    [_dpadBaseView.layer addSublayer:_dpadRightLayer];

    // Top-Left Shoulders: L2 (Heat A+B+C) stacked above L1 (Throw A+D)
    [self addButtonZone:MBAATouchControlHeatMacro
            visualStyle:MBAAPS2VisualStyleShoulderRect
                  title:@"L2"
            circularHit:NO
             hitPadding:6.0];
    [self addButtonZone:MBAATouchControlThrowMacro
            visualStyle:MBAAPS2VisualStyleShoulderRect
                  title:@"L1"
            circularHit:NO
             hitPadding:6.0];

    // Top-Right Shoulders: R2 (Dash A+B) stacked above R1 (E Quick Action)
    [self addButtonZone:MBAATouchControlDashMacro
            visualStyle:MBAAPS2VisualStyleShoulderRect
                  title:@"R2"
            circularHit:NO
             hitPadding:6.0];
    [self addButtonZone:MBAATouchControlBtnE
            visualStyle:MBAAPS2VisualStyleShoulderRect
                  title:@"R1"
            circularHit:NO
             hitPadding:6.0];

    // Bottom-Right PS2 Diamond Face Buttons: □ (A), △ (D), ○ (C), × (B)
    [self addButtonZone:MBAATouchControlBtnA
            visualStyle:MBAAPS2VisualStyleFaceSquare
                  title:nil
            circularHit:YES
             hitPadding:8.0];
    [self addButtonZone:MBAATouchControlBtnD
            visualStyle:MBAAPS2VisualStyleFaceTriangle
                  title:nil
            circularHit:YES
             hitPadding:8.0];
    [self addButtonZone:MBAATouchControlBtnC
            visualStyle:MBAAPS2VisualStyleFaceCircle
                  title:nil
            circularHit:YES
             hitPadding:8.0];
    [self addButtonZone:MBAATouchControlBtnB
            visualStyle:MBAAPS2VisualStyleFaceCross
                  title:nil
            circularHit:YES
             hitPadding:8.0];

    // Bottom-Center PS2 Trio: ▭ (SELECT -> FN1), ◎ (FN2), ▷ (START)
    [self addButtonZone:MBAATouchControlFN1
            visualStyle:MBAAPS2VisualStyleSelectRect
                  title:nil
            circularHit:NO
             hitPadding:8.0];
    [self addButtonZone:MBAATouchControlFN2
            visualStyle:MBAAPS2VisualStyleAnalogDoubleRing
                  title:nil
            circularHit:YES
             hitPadding:8.0];
    [self addButtonZone:MBAATouchControlStart
            visualStyle:MBAAPS2VisualStyleStartTriangle
                  title:nil
            circularHit:NO
             hitPadding:8.0];

    // Top-Right Pause Icon (||)
    [self addButtonZone:MBAATouchControlPause
            visualStyle:MBAAPS2VisualStylePauseBars
                  title:nil
            circularHit:NO
             hitPadding:8.0];

    // Discrete HUD settings button (monochrome AetherSX2 outline style, top-left sidebar)
    _hudSettingsButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [_hudSettingsButton setTitle:@"PAD" forState:UIControlStateNormal];
    _hudSettingsButton.titleLabel.font = [UIFont monospacedSystemFontOfSize:9.5 weight:UIFontWeightSemibold];
    [_hudSettingsButton setTitleColor:[UIColor colorWithWhite:1.0 alpha:0.85] forState:UIControlStateNormal];
    _hudSettingsButton.backgroundColor = [UIColor colorWithWhite:0.0 alpha:0.28];
    _hudSettingsButton.layer.cornerRadius = 3.0;
    _hudSettingsButton.layer.borderWidth = 1.25;
    _hudSettingsButton.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.45].CGColor;
    [_hudSettingsButton addTarget:self action:@selector(toggleSettingsPopover) forControlEvents:UIControlEventTouchUpInside];
    [self addSubview:_hudSettingsButton];

    // Controller auto-fade indicator badge
    _controllerBadgeLabel = [[UILabel alloc] initWithFrame:CGRectZero];
    _controllerBadgeLabel.font = [UIFont systemFontOfSize:10.0 weight:UIFontWeightSemibold];
    _controllerBadgeLabel.textColor = [UIColor colorWithWhite:0.95 alpha:1.0];
    _controllerBadgeLabel.backgroundColor = [UIColor colorWithWhite:0.06 alpha:0.80];
    _controllerBadgeLabel.textAlignment = NSTextAlignmentCenter;
    _controllerBadgeLabel.layer.cornerRadius = 6.0;
    _controllerBadgeLabel.layer.borderWidth = 1.0;
    _controllerBadgeLabel.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.35].CGColor;
    _controllerBadgeLabel.layer.masksToBounds = YES;
    _controllerBadgeLabel.text = @"GCController Active";
    _controllerBadgeLabel.alpha = 0.0;
    [self addSubview:_controllerBadgeLabel];

    [self setupSettingsPopover];
}

- (void)setupSettingsPopover {
    _settingsPopover = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 236, 126)];
    _settingsPopover.backgroundColor = [UIColor colorWithWhite:0.06 alpha:0.92];
    _settingsPopover.layer.cornerRadius = 8.0;
    _settingsPopover.layer.borderWidth = 1.25;
    _settingsPopover.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.40].CGColor;
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

- (void)addButtonZone:(MBAATouchControlTag)tag
          visualStyle:(MBAAPS2VisualStyle)style
                title:(nullable NSString*)title
          circularHit:(BOOL)circularHit
           hitPadding:(CGFloat)hitPadding {
    MBAAVirtualControlZone* zone = [[MBAAVirtualControlZone alloc] init];
    zone.tag = tag;
    zone.visualStyle = style;
    zone.title = title;
    zone.circularHit = circularHit;
    zone.hitPadding = hitPadding;

    UIView* container = [[UIView alloc] initWithFrame:CGRectZero];
    container.backgroundColor = [UIColor clearColor];
    container.userInteractionEnabled = NO;

    CAShapeLayer* outerLayer = [self makeVectorShapeLayer];
    if (style == MBAAPS2VisualStylePauseBars) {
        outerLayer.fillColor = [UIColor clearColor].CGColor;
        outerLayer.strokeColor = [UIColor clearColor].CGColor;
        outerLayer.lineWidth = 0.0;
    }
    [container.layer addSublayer:outerLayer];
    zone.outerLayer = outerLayer;

    BOOL needsSymbolLayer = (style == MBAAPS2VisualStyleFaceSquare ||
                             style == MBAAPS2VisualStyleFaceTriangle ||
                             style == MBAAPS2VisualStyleFaceCircle ||
                             style == MBAAPS2VisualStyleFaceCross ||
                             style == MBAAPS2VisualStyleAnalogDoubleRing ||
                             style == MBAAPS2VisualStylePauseBars);
    if (needsSymbolLayer) {
        CAShapeLayer* symbolLayer = [self makeVectorShapeLayer];
        if (style == MBAAPS2VisualStylePauseBars) {
            symbolLayer.fillColor = ps2IdleStrokeColor().CGColor;
            symbolLayer.strokeColor = [UIColor clearColor].CGColor;
            symbolLayer.lineWidth = 0.0;
        } else {
            symbolLayer.fillColor = [UIColor clearColor].CGColor;
            symbolLayer.strokeColor = ps2IdleStrokeColor().CGColor;
            symbolLayer.lineWidth = kPS2StrokeWidth;
        }
        [container.layer addSublayer:symbolLayer];
        zone.symbolLayer = symbolLayer;
    }

    if (title != nil) {
        UILabel* label = [[UILabel alloc] initWithFrame:CGRectZero];
        label.text = title;
        label.textAlignment = NSTextAlignmentCenter;
        label.textColor = [UIColor colorWithWhite:1.0 alpha:0.92];
        label.font = [UIFont systemFontOfSize:16.0 weight:UIFontWeightRegular];
        label.adjustsFontSizeToFitWidth = YES;
        label.minimumScaleFactor = 0.7;
        label.userInteractionEnabled = NO;
        [container addSubview:label];
        zone.labelView = label;
    }

    zone.containerView = container;
    [_controlsContainer addSubview:container];
    [_buttonZones addObject:zone];
}

#pragma mark - Vector Geometry Builders

- (void)rebuildDPadVectorPaths {
    CGRect bounds = _dpadBaseView.bounds;
    CGFloat size = MIN(bounds.size.width, bounds.size.height);
    if (size <= 0.0) {
        return;
    }

    CGFloat c = size * 0.5;
    CGFloat pad = kPS2StrokeWidth * 0.5;
    CGFloat outerR = c - pad;
    CGFloat halfBreadth = size * 0.105;
    CGFloat shankLen = size * 0.205;
    CGFloat bevelR = outerR - shankLen;
    CGFloat tipLen = size * 0.108;
    CGFloat tipR = bevelR - tipLen;

    // Up arrow pentagon (flat top, inward point facing center)
    UIBezierPath* upPath = [UIBezierPath bezierPath];
    [upPath moveToPoint:CGPointMake(c - halfBreadth, c - outerR)];
    [upPath addLineToPoint:CGPointMake(c + halfBreadth, c - outerR)];
    [upPath addLineToPoint:CGPointMake(c + halfBreadth, c - bevelR)];
    [upPath addLineToPoint:CGPointMake(c, c - tipR)];
    [upPath addLineToPoint:CGPointMake(c - halfBreadth, c - bevelR)];
    [upPath closePath];

    // Down arrow pentagon (flat bottom, inward point facing center)
    UIBezierPath* downPath = [UIBezierPath bezierPath];
    [downPath moveToPoint:CGPointMake(c - halfBreadth, c + outerR)];
    [downPath addLineToPoint:CGPointMake(c + halfBreadth, c + outerR)];
    [downPath addLineToPoint:CGPointMake(c + halfBreadth, c + bevelR)];
    [downPath addLineToPoint:CGPointMake(c, c + tipR)];
    [downPath addLineToPoint:CGPointMake(c - halfBreadth, c + bevelR)];
    [downPath closePath];

    // Left arrow pentagon (flat left, inward point facing center)
    UIBezierPath* leftPath = [UIBezierPath bezierPath];
    [leftPath moveToPoint:CGPointMake(c - outerR, c - halfBreadth)];
    [leftPath addLineToPoint:CGPointMake(c - bevelR, c - halfBreadth)];
    [leftPath addLineToPoint:CGPointMake(c - tipR, c)];
    [leftPath addLineToPoint:CGPointMake(c - bevelR, c + halfBreadth)];
    [leftPath addLineToPoint:CGPointMake(c - outerR, c + halfBreadth)];
    [leftPath closePath];

    // Right arrow pentagon (flat right, inward point facing center)
    UIBezierPath* rightPath = [UIBezierPath bezierPath];
    [rightPath moveToPoint:CGPointMake(c + outerR, c - halfBreadth)];
    [rightPath addLineToPoint:CGPointMake(c + bevelR, c - halfBreadth)];
    [rightPath addLineToPoint:CGPointMake(c + tipR, c)];
    [rightPath addLineToPoint:CGPointMake(c + bevelR, c + halfBreadth)];
    [rightPath addLineToPoint:CGPointMake(c + outerR, c + halfBreadth)];
    [rightPath closePath];

    CGFloat displayScale = [self currentDisplayScale];
    [CATransaction begin];
    [CATransaction setDisableActions:YES];
    _dpadUpLayer.contentsScale = displayScale;
    _dpadDownLayer.contentsScale = displayScale;
    _dpadLeftLayer.contentsScale = displayScale;
    _dpadRightLayer.contentsScale = displayScale;
    _dpadUpLayer.frame = bounds;
    _dpadDownLayer.frame = bounds;
    _dpadLeftLayer.frame = bounds;
    _dpadRightLayer.frame = bounds;
    _dpadUpLayer.path = upPath.CGPath;
    _dpadDownLayer.path = downPath.CGPath;
    _dpadLeftLayer.path = leftPath.CGPath;
    _dpadRightLayer.path = rightPath.CGPath;
    [CATransaction commit];
}

- (void)rebuildVectorPathsForZone:(MBAAVirtualControlZone*)zone scale:(CGFloat)scale {
    CGRect bounds = zone.containerView.bounds;
    CGFloat w = bounds.size.width;
    CGFloat h = bounds.size.height;
    if (w <= 0.0 || h <= 0.0) {
        return;
    }

    CGFloat halfStroke = kPS2StrokeWidth * 0.5;
    CGRect insetRect = CGRectInset(bounds, halfStroke, halfStroke);
    CGFloat d = MIN(w, h);
    CGFloat cx = CGRectGetMidX(bounds);
    CGFloat cy = CGRectGetMidY(bounds);

    UIBezierPath* outerPath = nil;
    UIBezierPath* symbolPath = nil;

    switch (zone.visualStyle) {
        case MBAAPS2VisualStyleShoulderRect:
        case MBAAPS2VisualStyleSelectRect: {
            outerPath = [UIBezierPath bezierPathWithRect:insetRect];
            break;
        }
        case MBAAPS2VisualStyleFaceSquare: {
            outerPath = [UIBezierPath bezierPathWithOvalInRect:insetRect];
            CGFloat side = d * 0.48;
            symbolPath = [UIBezierPath bezierPathWithRect:CGRectMake(cx - side * 0.5, cy - side * 0.5, side, side)];
            break;
        }
        case MBAAPS2VisualStyleFaceTriangle: {
            outerPath = [UIBezierPath bezierPathWithOvalInRect:insetRect];
            CGFloat r = d * 0.34;
            CGFloat optY = d * 0.035;
            CGFloat dx = r * 0.8660254;
            symbolPath = [UIBezierPath bezierPath];
            [symbolPath moveToPoint:CGPointMake(cx, cy + optY - r)];
            [symbolPath addLineToPoint:CGPointMake(cx + dx, cy + optY + r * 0.5)];
            [symbolPath addLineToPoint:CGPointMake(cx - dx, cy + optY + r * 0.5)];
            [symbolPath closePath];
            break;
        }
        case MBAAPS2VisualStyleFaceCircle: {
            outerPath = [UIBezierPath bezierPathWithOvalInRect:insetRect];
            CGFloat r = d * 0.285;
            symbolPath = [UIBezierPath bezierPathWithOvalInRect:CGRectMake(cx - r, cy - r, r * 2.0, r * 2.0)];
            break;
        }
        case MBAAPS2VisualStyleFaceCross: {
            outerPath = [UIBezierPath bezierPathWithOvalInRect:insetRect];
            CGFloat arm = d * 0.225;
            symbolPath = [UIBezierPath bezierPath];
            [symbolPath moveToPoint:CGPointMake(cx - arm, cy - arm)];
            [symbolPath addLineToPoint:CGPointMake(cx + arm, cy + arm)];
            [symbolPath moveToPoint:CGPointMake(cx + arm, cy - arm)];
            [symbolPath addLineToPoint:CGPointMake(cx - arm, cy + arm)];
            break;
        }
        case MBAAPS2VisualStyleAnalogDoubleRing: {
            outerPath = [UIBezierPath bezierPathWithOvalInRect:insetRect];
            CGFloat innerDia = d * 0.36;
            symbolPath = [UIBezierPath bezierPathWithOvalInRect:CGRectMake(cx - innerDia * 0.5,
                                                                           cy - innerDia * 0.5,
                                                                           innerDia,
                                                                           innerDia)];
            break;
        }
        case MBAAPS2VisualStyleStartTriangle: {
            outerPath = [UIBezierPath bezierPath];
            [outerPath moveToPoint:CGPointMake(CGRectGetMinX(insetRect), CGRectGetMinY(insetRect))];
            [outerPath addLineToPoint:CGPointMake(CGRectGetMaxX(insetRect), CGRectGetMidY(insetRect))];
            [outerPath addLineToPoint:CGPointMake(CGRectGetMinX(insetRect), CGRectGetMaxY(insetRect))];
            [outerPath closePath];
            break;
        }
        case MBAAPS2VisualStylePauseBars: {
            outerPath = [UIBezierPath bezierPathWithRoundedRect:bounds cornerRadius:6.0];
            CGFloat barW = 5.5 * scale;
            CGFloat barH = 20.0 * scale;
            CGFloat barGap = 5.5 * scale;
            CGFloat totalW = barW * 2.0 + barGap;
            CGFloat bx = cx - totalW * 0.5;
            CGFloat by = cy - barH * 0.5;
            symbolPath = [UIBezierPath bezierPathWithRect:CGRectMake(bx, by, barW, barH)];
            [symbolPath appendPath:[UIBezierPath bezierPathWithRect:CGRectMake(bx + barW + barGap, by, barW, barH)]];
            break;
        }
    }

    CGFloat displayScale = [self currentDisplayScale];
    [CATransaction begin];
    [CATransaction setDisableActions:YES];
    zone.outerLayer.contentsScale = displayScale;
    zone.outerLayer.frame = bounds;
    zone.outerLayer.path = outerPath.CGPath;
    if (zone.symbolLayer != nil) {
        zone.symbolLayer.contentsScale = displayScale;
        zone.symbolLayer.frame = bounds;
        zone.symbolLayer.path = symbolPath.CGPath;
    }
    [CATransaction commit];

    if (zone.labelView != nil) {
        zone.labelView.frame = CGRectInset(bounds, 4.0, 2.0);
        zone.labelView.font = [UIFont systemFontOfSize:round(16.0 * scale) weight:UIFontWeightRegular];
    }
}

#pragma mark - Layout (AetherSX2 PS2 Layout Tuned for iPhone SE 2020: 667x375 pt)

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
    if (w <= 0.0 || h <= 0.0) {
        return;
    }

    UIEdgeInsets safe = UIEdgeInsetsZero;
    if (@available(iOS 11.0, *)) {
        safe = self.safeAreaInsets;
    }

    CGFloat usableW = MAX(320.0, w - safe.left - safe.right);
    CGFloat scale = MIN(1.05, MAX(0.70, MIN(h / 375.0, usableW / 640.0)));

    CGFloat leftEdge = safe.left + 12.0;
    CGFloat rightEdge = w - safe.right - 12.0;
    CGFloat topEdge = safe.top + 8.0;
    CGFloat bottomMargin = MAX(10.0, safe.bottom * 0.65);

    // Symmetric left/right cluster dimensions (matches AetherSX2 PS2 screenshot proportions)
    CGFloat dpadSize = round(148.0 * scale);
    CGFloat faceDia = round(52.0 * scale);
    CGFloat diamondOffset = round(48.0 * scale);
    CGFloat clusterHalfSpan = MAX(dpadSize * 0.5, diamondOffset + faceDia * 0.5);

    CGFloat leftClusterCenterX = leftEdge + clusterHalfSpan + round(8.0 * scale);
    CGFloat rightClusterCenterX = rightEdge - clusterHalfSpan - round(8.0 * scale);
    CGFloat clusterCenterY = h - bottomMargin - round(16.0 * scale) - clusterHalfSpan;

    // Bottom-Left: PS2 4-way D-Pad (8-way thumb sliding with generous hit margin)
    _dpadFrame = CGRectMake(leftClusterCenterX - dpadSize * 0.5,
                            clusterCenterY - dpadSize * 0.5,
                            dpadSize,
                            dpadSize);
    _dpadHitRect = CGRectInset(_dpadFrame, -round(22.0 * scale), -round(22.0 * scale));
    _dpadBaseView.frame = _dpadFrame;
    [self rebuildDPadVectorPaths];
    [self updateDPadVisuals];

    // Stacked rectangular shoulder buttons: L2/L1 (top-left) and R2/R1 (top-right)
    CGFloat shoulderW = round(72.0 * scale);
    CGFloat shoulderH = round(34.0 * scale);
    CGFloat shoulderGap = round(14.0 * scale);
    CGFloat shoulderTopY = MAX(topEdge + round(44.0 * scale), round(56.0 * scale));
    // Guarantee comfortable clearance above D-pad / face diamond on compact heights
    CGFloat maxShoulderBottomY = CGRectGetMinY(_dpadFrame) - round(24.0 * scale);
    CGFloat neededShoulderSpan = shoulderH * 2.0 + shoulderGap;
    if (shoulderTopY + neededShoulderSpan > maxShoulderBottomY) {
        shoulderTopY = MAX(topEdge + round(34.0 * scale), maxShoulderBottomY - neededShoulderSpan);
    }

    CGFloat l2X = leftClusterCenterX - shoulderW * 0.5;
    CGFloat r2X = rightClusterCenterX - shoulderW * 0.5;
    CGFloat l1Y = shoulderTopY + shoulderH + shoulderGap;

    [self setFrame:CGRectMake(l2X, shoulderTopY, shoulderW, shoulderH) forTag:MBAATouchControlHeatMacro scale:scale];
    [self setFrame:CGRectMake(l2X, l1Y,          shoulderW, shoulderH) forTag:MBAATouchControlThrowMacro scale:scale];
    [self setFrame:CGRectMake(r2X, shoulderTopY, shoulderW, shoulderH) forTag:MBAATouchControlDashMacro scale:scale];
    [self setFrame:CGRectMake(r2X, l1Y,          shoulderW, shoulderH) forTag:MBAATouchControlBtnE scale:scale];

    // Bottom-Right: PS2 Diamond Face Buttons (□ Left=A, △ Top=D, ○ Right=C, × Bottom=B)
    CGFloat faceR = faceDia * 0.5;
    [self setFrame:CGRectMake(rightClusterCenterX - diamondOffset - faceR, clusterCenterY - faceR,                 faceDia, faceDia)
            forTag:MBAATouchControlBtnA scale:scale];
    [self setFrame:CGRectMake(rightClusterCenterX - faceR,                 clusterCenterY - diamondOffset - faceR, faceDia, faceDia)
            forTag:MBAATouchControlBtnD scale:scale];
    [self setFrame:CGRectMake(rightClusterCenterX + diamondOffset - faceR, clusterCenterY - faceR,                 faceDia, faceDia)
            forTag:MBAATouchControlBtnC scale:scale];
    [self setFrame:CGRectMake(rightClusterCenterX - faceR,                 clusterCenterY + diamondOffset - faceR, faceDia, faceDia)
            forTag:MBAATouchControlBtnB scale:scale];

    // Bottom-Center Cluster: ▭ SELECT (FN1), ◎ FN2, ▷ START
    CGFloat selectW = round(42.0 * scale);
    CGFloat selectH = round(24.0 * scale);
    CGFloat analogDia = round(24.0 * scale);
    CGFloat startW = round(42.0 * scale);
    CGFloat startH = round(24.0 * scale);
    CGFloat centerGap = round(18.0 * scale);
    CGFloat totalCenterW = selectW + centerGap + analogDia + centerGap + startW;
    CGFloat midX = CGRectIsEmpty(viewportRect) ? (w * 0.5) : CGRectGetMidX(viewportRect);
    CGFloat centerRowY = h - bottomMargin - selectH;
    CGFloat curX = midX - totalCenterW * 0.5;

    [self setFrame:CGRectMake(curX, centerRowY, selectW, selectH) forTag:MBAATouchControlFN1 scale:scale];
    curX += selectW + centerGap;
    [self setFrame:CGRectMake(curX, centerRowY + (selectH - analogDia) * 0.5, analogDia, analogDia) forTag:MBAATouchControlFN2 scale:scale];
    curX += analogDia + centerGap;
    [self setFrame:CGRectMake(curX, centerRowY + (selectH - startH) * 0.5, startW, startH) forTag:MBAATouchControlStart scale:scale];

    // Top-Right Corner: Crisp || Pause Icon (clear of Metal HUD and R2)
    CGFloat pauseW = round(38.0 * scale);
    CGFloat pauseH = round(30.0 * scale);
    [self setFrame:CGRectMake(rightEdge - pauseW, topEdge, pauseW, pauseH) forTag:MBAATouchControlPause scale:scale];

    // Discrete Top-Left PAD Opacity/Hide Settings Toggle (in left sidebar, clear of L2 & HUD)
    CGFloat hudBtnW = 36.0;
    CGFloat hudBtnH = 22.0;
    _hudSettingsButton.frame = CGRectMake(leftEdge, topEdge, hudBtnW, hudBtnH);
    _settingsPopover.frame = CGRectMake(leftEdge, topEdge + hudBtnH + 8.0, 236.0, 126.0);
    _controllerBadgeLabel.frame = CGRectMake(midX - 72.0, topEdge, 144.0, 22.0);
}

- (void)setFrame:(CGRect)frame forTag:(MBAATouchControlTag)tag scale:(CGFloat)scale {
    for (MBAAVirtualControlZone* zone in _buttonZones) {
        if (zone.tag == tag) {
            zone.frame = frame;
            zone.containerView.transform = CGAffineTransformIdentity;
            zone.containerView.frame = frame;
            [self rebuildVectorPathsForZone:zone scale:scale];
            if (zone.pressed) {
                zone.containerView.transform = CGAffineTransformMakeScale(0.95, 0.95);
            }
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

- (void)resetAllInputs {
    BOOL hadActive = (_dpadTouch != nil) || (_activeTouches.count > 0) || (_dpadMask != 0) || (_currentState.buttons != 0);
    _dpadTouch = nil;
    [_activeTouches removeAllObjects];
    [self resetDPad];
    if (hadActive) {
        [self recomputeButtonStates];
    }
}

- (void)applyEffectiveOpacityAnimated:(BOOL)animated {
    BOOL hidePad = (_manualHidden || _controllerConnected);
    if (hidePad) {
        [self resetAllInputs];
    }
    CGFloat targetAlpha = hidePad ? 0.0 : _userOpacity;
    CGFloat padBtnAlpha = hidePad ? 0.28 : 0.65;
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

    if ([self controlZoneAtPoint:point] != nil || (!_manualHidden && !_controllerConnected && CGRectContainsPoint(_dpadHitRect, point))) {
        return self;
    }
    return nil;
}

- (nullable MBAAVirtualControlZone*)controlZoneAtPoint:(CGPoint)point {
    if (_manualHidden || _controllerConnected) {
        return nil;
    }

    MBAAVirtualControlZone* bestZone = nil;
    CGFloat bestDistSq = CGFLOAT_MAX;

    for (MBAAVirtualControlZone* zone in _buttonZones) {
        CGPoint center = CGPointMake(CGRectGetMidX(zone.frame), CGRectGetMidY(zone.frame));
        CGFloat dx = point.x - center.x;
        CGFloat dy = point.y - center.y;
        CGFloat distSq = dx * dx + dy * dy;

        BOOL inside = NO;
        if (zone.circularHit) {
            CGFloat hitRadius = MIN(zone.frame.size.width, zone.frame.size.height) * 0.5 + zone.hitPadding;
            inside = (distSq <= hitRadius * hitRadius);
        } else {
            CGRect hitFrame = CGRectInset(zone.frame, -zone.hitPadding, -zone.hitPadding);
            inside = CGRectContainsPoint(hitFrame, point);
        }

        if (inside && distSq < bestDistSq) {
            bestDistSq = distSq;
            bestZone = zone;
        }
    }
    return bestZone;
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
            continue;
        }

        NSNumber* existingTag = [_activeTouches objectForKey:touch];
        if (existingTag != nil && existingTag.integerValue == MBAATouchControlPause) {
            // Keep Pause taps isolated so dragging off || never triggers R2/face attacks.
            MBAAVirtualControlZone* pauseZone = [self controlZoneAtPoint:pt];
            if (pauseZone == nil || pauseZone.tag != MBAATouchControlPause) {
                [_activeTouches removeObjectForKey:touch];
            }
            continue;
        }

        // Smooth thumb-sliding across face diamond (□/△/○/×), shoulders, and center buttons
        MBAAVirtualControlZone* zone = [self controlZoneAtPoint:pt];
        if (zone != nil && zone.tag != MBAATouchControlPause) {
            [_activeTouches setObject:@(zone.tag) forKey:touch];
        } else if (existingTag != nil) {
            [_activeTouches removeObjectForKey:touch];
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
    if (radius <= 0.0) {
        return;
    }

    CGFloat dx = point.x - center.x;
    CGFloat dy = center.y - point.y;  // +Y = Up
    CGFloat dist = hypot(dx, dy);

    CGFloat deadzone = radius * 0.18;
    if (dist < deadzone) {
        _dpadX = 0.0;
        _dpadY = 0.0;
        _dpadMask = 0;
        [self updateDPadVisuals];
        return;
    }

    CGFloat clamped = MIN(dist, radius);
    _dpadX = (dx / dist) * (clamped / radius);
    _dpadY = (dy / dist) * (clamped / radius);

    // 8-way sectorization (22.5 deg boundaries -> 8 equal 45 deg wedges)
    // Supports clean fighting-game motions (236, 623, 214, IAD) with simultaneous cardinal bits on diagonals.
    double angleDeg = atan2(dy, dx) * (180.0 / M_PI);
    if (angleDeg < 0.0) {
        angleDeg += 360.0;
    }
    int sector = ((int)floor((angleDeg + 22.5) / 45.0)) % 8;

    static const uint32_t kSectorMasks[8] = {
        MBAAVirtualButtonRight,                         // 0: E  (6)
        MBAAVirtualButtonRight | MBAAVirtualButtonUp,   // 1: NE (9)
        MBAAVirtualButtonUp,                            // 2: N  (8)
        MBAAVirtualButtonLeft  | MBAAVirtualButtonUp,   // 3: NW (7)
        MBAAVirtualButtonLeft,                          // 4: W  (4)
        MBAAVirtualButtonLeft  | MBAAVirtualButtonDown, // 5: SW (1)
        MBAAVirtualButtonDown,                          // 6: S  (2)
        MBAAVirtualButtonRight | MBAAVirtualButtonDown, // 7: SE (3)
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

- (void)applyVisualStateForDPadLayer:(CAShapeLayer*)layer active:(BOOL)active {
    layer.fillColor = active ? ps2PressedFillColor().CGColor : ps2IdleFillColor().CGColor;
    layer.strokeColor = active ? ps2PressedStrokeColor().CGColor : ps2IdleStrokeColor().CGColor;
}

- (void)updateDPadVisuals {
    [CATransaction begin];
    [CATransaction setDisableActions:YES];
    [self applyVisualStateForDPadLayer:_dpadUpLayer    active:((_dpadMask & MBAAVirtualButtonUp) != 0)];
    [self applyVisualStateForDPadLayer:_dpadDownLayer  active:((_dpadMask & MBAAVirtualButtonDown) != 0)];
    [self applyVisualStateForDPadLayer:_dpadLeftLayer  active:((_dpadMask & MBAAVirtualButtonLeft) != 0)];
    [self applyVisualStateForDPadLayer:_dpadRightLayer active:((_dpadMask & MBAAVirtualButtonRight) != 0)];
    [CATransaction commit];
}

- (void)applyVisualStateForZone:(MBAAVirtualControlZone*)zone active:(BOOL)active {
    if (zone.visualStyle == MBAAPS2VisualStylePauseBars) {
        zone.outerLayer.fillColor = active ? [UIColor colorWithWhite:1.0 alpha:0.24].CGColor : [UIColor clearColor].CGColor;
        zone.symbolLayer.fillColor = active ? ps2PressedStrokeColor().CGColor : ps2IdleStrokeColor().CGColor;
    } else {
        zone.outerLayer.fillColor = active ? ps2PressedFillColor().CGColor : ps2IdleFillColor().CGColor;
        zone.outerLayer.strokeColor = active ? ps2PressedStrokeColor().CGColor : ps2IdleStrokeColor().CGColor;
        if (zone.symbolLayer != nil) {
            zone.symbolLayer.strokeColor = active ? ps2PressedStrokeColor().CGColor : ps2IdleStrokeColor().CGColor;
        }
        if (zone.labelView != nil) {
            zone.labelView.textColor = active ? [UIColor whiteColor] : [UIColor colorWithWhite:1.0 alpha:0.92];
        }
    }
    zone.containerView.transform = active ? CGAffineTransformMakeScale(0.95, 0.95) : CGAffineTransformIdentity;
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
    [CATransaction begin];
    [CATransaction setDisableActions:YES];
    for (MBAAVirtualControlZone* zone in _buttonZones) {
        BOOL active = zone.pressed;
        [self applyVisualStateForZone:zone active:active];

        if (!active) continue;
        switch (zone.tag) {
            case MBAATouchControlBtnA: mask |= MBAAVirtualButtonA; break;
            case MBAATouchControlBtnB: mask |= MBAAVirtualButtonB; break;
            case MBAATouchControlBtnC: mask |= MBAAVirtualButtonC; break;
            case MBAATouchControlBtnD: mask |= MBAAVirtualButtonD; break;
            case MBAATouchControlBtnE: mask |= MBAAVirtualButtonE; break;
            case MBAATouchControlThrowMacro:
                mask |= (MBAAVirtualButtonA | MBAAVirtualButtonD);
                break;
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
    [CATransaction commit];

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
