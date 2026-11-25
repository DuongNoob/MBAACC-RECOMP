#import <UIKit/UIKit.h>
#include <stdint.h>

NS_ASSUME_NONNULL_BEGIN

/// Bitmask layout for virtual touch controls matching MBAACC arcade + macro inputs.
typedef NS_OPTIONS(uint32_t, MBAAVirtualButtonMask) {
    MBAAVirtualButtonNone  = 0,
    MBAAVirtualButtonUp    = 1u << 0,
    MBAAVirtualButtonDown  = 1u << 1,
    MBAAVirtualButtonLeft  = 1u << 2,
    MBAAVirtualButtonRight = 1u << 3,
    MBAAVirtualButtonA     = 1u << 4,
    MBAAVirtualButtonB     = 1u << 5,
    MBAAVirtualButtonC     = 1u << 6,
    MBAAVirtualButtonD     = 1u << 7,
    MBAAVirtualButtonE     = 1u << 8,
    MBAAVirtualButtonStart = 1u << 9,
    MBAAVirtualButtonCoin  = 1u << 10,
    MBAAVirtualButtonFN1   = 1u << 11,
    MBAAVirtualButtonFN2   = 1u << 12,
    MBAAVirtualButtonPause = 1u << 13,
    MBAAVirtualButtonDash  = 1u << 14,  // Convenience macro: A + B
    MBAAVirtualButtonHeat  = 1u << 15,  // Convenience macro: A + B + C
};

typedef struct MBAAVirtualPadState {
    uint32_t buttons;  // Combination of MBAAVirtualButtonMask flags (macros expand A+B / A+B+C)
    float dpadX;       // Normalized [-1.0, +1.0]
    float dpadY;       // Normalized [-1.0, +1.0] (+1 up, -1 down)
} MBAAVirtualPadState;

@class TouchOverlayView;

@protocol TouchOverlayViewDelegate <NSObject>
@optional
- (void)touchOverlayView:(TouchOverlayView*)overlay didUpdatePadState:(MBAAVirtualPadState)state;
- (void)touchOverlayViewDidTogglePause:(TouchOverlayView*)overlay;
- (void)touchOverlayViewDidRequestResetCheck:(TouchOverlayView*)overlay;
@end

/// Ergonomic multi-touch fighting-game overlay tuned for iPhone SE 2020 (1334x750, 16:9).
/// A centered 4:3 game viewport (1000x750 px / 500x375 pt) leaves 167 px (83.5 pt) sidebars
/// on both left and right edges for D-pad, attack buttons, macros, and utility controls.
@interface TouchOverlayView : UIView

@property (nonatomic, weak, nullable) id<TouchOverlayViewDelegate> delegate;
@property (nonatomic, assign, readonly) MBAAVirtualPadState currentState;
@property (nonatomic, assign) CGFloat userOpacity;
@property (nonatomic, assign, getter=isManualHidden) BOOL manualHidden;
@property (nonatomic, assign, readonly, getter=isControllerConnected) BOOL controllerConnected;

/// Recomputes control frames for the current view bounds & centered 4:3 viewport rect.
- (void)updateLayoutForViewportRect:(CGRect)viewportRect;

@end

NS_ASSUME_NONNULL_END
