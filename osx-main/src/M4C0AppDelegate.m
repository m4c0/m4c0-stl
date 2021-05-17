#import "M4C0AppDelegate.h"
#import "M4C0View.h"
#include "main.h"

#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

@interface M4C0AppDelegate ()
@property (nonatomic, strong) NSWindow * window;
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
  self.window = [[NSWindow alloc] init];
  self.window.contentView = [[M4C0View alloc] init];
  self.window.delegate = self.windowDelegate;
  self.window.acceptsMouseMovedEvents = YES;
  self.window.title = appName;
  self.window.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
                        | NSWindowStyleMaskResizable;
  self.window.collectionBehavior = NSWindowCollectionBehaviorFullScreenPrimary;

  [self.window setFrame:CGRectMake(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) display:TRUE];
  [self.window center];
  [self.window makeKeyAndOrderFront:self.window];
}

@end
