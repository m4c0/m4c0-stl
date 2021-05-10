#import "M4C0AppDelegate.h"

#if !__has_feature(objc_arc)
#error "ARC is off"
#endif

void m4c0_osx_main() {
  M4C0AppDelegate * delegate = [[M4C0AppDelegate alloc] init];

  NSApplication * app = [NSApplication sharedApplication];
  app.delegate = delegate;

  [app run];
}
