#import "M4C0AppDelegate.h"
#import "M4C0Window.h"

#import <MetalKit/MetalKit.h>
#include <m4c0/objc/middleware.hpp>

const id m4c0_dummy = @[ @protocol(NSWindowDelegate), @protocol(MTKViewDelegate) ];

static id create_class(const char * base_class) {
  return (__bridge id)m4c0::objc::middleware::instance().create_for_class(base_class);
}
static id create_proto(const char * base_class) {
  return (__bridge id)m4c0::objc::middleware::instance().create_for_protocol(base_class);
}

@interface M4C0AppDelegate ()
@property (nonatomic, strong) M4C0Window * window;
@property (nonatomic, strong) id viewDelegate;
@property (nonatomic, strong) id windowDelegate;

- (void)createAppleMenu:(NSString *)appName;
- (void)createWindow:(NSString *)appName;
@end

@implementation M4C0AppDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
  return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
  NSDictionary * info = [[NSBundle mainBundle] infoDictionary];
  NSString * appName = [info objectForKey:@"CFBundleName"];
  if (appName == nullptr) appName = @"App";

  [self createWindow:appName];
  [self createAppleMenu:appName];

  [NSApp activateIgnoringOtherApps:YES];
}

- (void)createWindow:(NSString *)appName {
  self.windowDelegate = create_proto("NSWindowDelegate");
  self.viewDelegate = create_proto("MTKViewDelegate");

  id view = create_class("MTKView");
  [view setDelegate:self.viewDelegate];

  self.window = [[M4C0Window alloc] init];
  self.window.contentView = view;
  [self.window setDelegate:self.windowDelegate];
  [self.window setupWithTitle:appName];
}

- (void)createAppleMenu:(NSString *)appName {
  NSMenu * bar = [[NSMenu alloc] init];

  NSMenuItem * appItem = [[NSMenuItem alloc] init];
  NSMenu * appMenu = [[NSMenu alloc] init];
  [appMenu addItem:[[NSMenuItem alloc] initWithTitle:[@"Hide " stringByAppendingString:appName]
                                              action:@selector(hide:)
                                       keyEquivalent:@"h"]];
  NSMenuItem * hideOthers = [[NSMenuItem alloc] initWithTitle:@"Hide Others"
                                                       action:@selector(hideOtherApplications:)
                                                keyEquivalent:@"h"];
  hideOthers.keyEquivalentModifierMask |= NSEventModifierFlagOption;
  [appMenu addItem:hideOthers];
  [appMenu addItem:[[NSMenuItem alloc] initWithTitle:@"Show All"
                                              action:@selector(unhideAllApplications:)
                                       keyEquivalent:@""]];
  [appMenu addItem:[NSMenuItem separatorItem]];
  [appMenu addItem:[[NSMenuItem alloc] initWithTitle:[@"Quit " stringByAppendingString:appName]
                                              action:@selector(terminate:)
                                       keyEquivalent:@"q"]];
  [appItem setSubmenu:appMenu];
  [bar addItem:appItem];

  [NSApp setMainMenu:bar];
}

@end
