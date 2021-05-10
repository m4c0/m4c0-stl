@import MetalKit;
@import UIKit;

#include "main.h"

@interface M4C0AppDelegate : NSObject<UIApplicationDelegate>
@property (nonatomic, strong) UIWindow * window;
@end
@implementation M4C0AppDelegate
- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions {

  UIViewController * vc = [[UIViewController alloc] init];
  vc.view = [[MTKView alloc] init];

  CGRect frame = [[UIScreen mainScreen] bounds];
  self.window = [[UIWindow alloc] initWithFrame:frame];
  self.window.rootViewController = vc;
  [self.window makeKeyAndVisible];

  m4c0_ios_main_start((__bridge void *)(vc.view));

  return YES;
}
- (void)applicationWillTerminate:(UIApplication *)application {
  m4c0_ios_main_stop();
}

@end
