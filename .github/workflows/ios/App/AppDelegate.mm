#import "AppDelegate.h"
#import "GameViewController.h"

@interface AppDelegate ()
@property (nonatomic, weak) GameViewController* gameViewController;
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication*)application
    didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id>*)launchOptions {
    (void)application;
    (void)launchOptions;

    CGRect bounds = [UIScreen mainScreen].bounds;
    self.window = [[UIWindow alloc] initWithFrame:bounds];

    GameViewController* gvc = [[GameViewController alloc] init];
    self.gameViewController = gvc;

    self.window.rootViewController = gvc;
    self.window.backgroundColor = [UIColor blackColor];
    [self.window makeKeyAndVisible];

    return YES;
}

- (void)applicationWillResignActive:(UIApplication*)application {
    (void)application;
    [self.gameViewController setPausedBySystem:YES];
}

- (void)applicationDidEnterBackground:(UIApplication*)application {
    (void)application;
    [self.gameViewController setPausedBySystem:YES];
}

- (void)applicationDidBecomeActive:(UIApplication*)application {
    (void)application;
    [self.gameViewController setPausedBySystem:NO];
}

- (void)applicationWillTerminate:(UIApplication*)application {
    (void)application;
    [self.gameViewController shutdownEngine];
}

@end
