#import "M4C0AppDelegate.h"
#include "main.h"

#import <Cocoa/Cocoa.h>

@implementation M4C0AppDelegate

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
  return YES;
}

- (void)applicationWillTerminate:(NSNotification *)notification {
  m4c0_osx_main_stop();
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification {
}
@end
