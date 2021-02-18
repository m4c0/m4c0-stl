#import "M4C0AppDelegate.h"
#import "M4C0Window.h"

#include <m4c0/osx/main.hpp>
#include <objc/runtime.h>

@interface M4C0AppDelegate ()
@property (nonatomic, strong) M4C0Window * window;
@property (nonatomic, strong) id<NSWindowDelegate> windowDelegate;
@property (nonatomic, strong) id viewDelegate;

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
  self.viewDelegate = [[objc_getClass(m4c0::osx::view_delegate_classname()) alloc] init];

  id view = [[objc_getClass(m4c0::osx::view_classname()) alloc] init];
  [view setDelegate:self.viewDelegate];

  self.window = [[M4C0Window alloc] init];
  self.window.contentView = view;
  self.window.delegate = self.windowDelegate = [[objc_getClass(m4c0::osx::window_delegate_classname()) alloc] init];
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
