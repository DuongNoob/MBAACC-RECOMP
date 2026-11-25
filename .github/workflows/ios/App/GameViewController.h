#import <MetalKit/MetalKit.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface GameViewController : UIViewController <MTKViewDelegate>

- (void)setPausedBySystem:(BOOL)paused;
- (void)shutdownEngine;

@end

NS_ASSUME_NONNULL_END
