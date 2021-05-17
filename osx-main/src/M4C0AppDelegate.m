#import "M4C0AppDelegate.h"
#import "M4C0View.h"
#import "M4C0Window.h"
#include "main.h"

#import <MetalKit/MetalKit.h>

@interface M4C0AppDelegate ()
@property (nonatomic, strong) M4C0Window * window;
@property (nonatomic, strong) id windowDelegate;

- (void)createWindow:(NSString *)appName;
@end

@implementation M4C0AppDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
  return YES;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
  m4c0_osx_main_stop();
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  NSDictionary * info = [[NSBundle mainBundle] infoDictionary];
  NSString * appName = [info objectForKey:@"CFBundleName"];
  if (appName == nil) appName = @"App";

  [self createWindow:appName];

  [NSApp activateIgnoringOtherApps:YES];

  m4c0_osx_main_start((__bridge void *)(self.window.contentView));
}

- (void)createWindow:(NSString *)appName {
  self.window = [[M4C0Window alloc] init];
  self.window.contentView = [[M4C0View alloc] init];
  [self.window setDelegate:self.windowDelegate];
  [self.window setupWithTitle:appName];
}

@end
