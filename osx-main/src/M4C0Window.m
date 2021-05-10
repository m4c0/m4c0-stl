#import "M4C0Window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

@implementation M4C0Window

- (void)setupWithTitle:(NSString *)title {
  self.acceptsMouseMovedEvents = YES;
  self.title = title;
  self.styleMask = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
                 | NSWindowStyleMaskResizable;
  self.collectionBehavior = NSWindowCollectionBehaviorFullScreenPrimary;

  [self setFrame:CGRectMake(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT) display:TRUE];
  [self center];
  [self makeKeyAndOrderFront:self];
}

@end
