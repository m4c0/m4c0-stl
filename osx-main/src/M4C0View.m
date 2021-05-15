#import "M4C0View.h"

@implementation M4C0View
// http://smokyonion.github.io/blog/2012/11/11/how-to-make-your-mac-apps-retina-ready/
- (void)_updateContentScale {
  NSWindow * mainWindow = [NSApp mainWindow];
  NSWindow * layerWindow = [self window];
  if (mainWindow || layerWindow) {
    CGFloat scale = [(layerWindow != nil) ? layerWindow : mainWindow backingScaleFactor];
    CALayer * layer = self.layer;
    if ([layer respondsToSelector:@selector(contentsScale)]) {
      [self.layer setContentsScale:scale];
    }
  }
}

- (void)scaleDidChange:(NSNotification *)n {
  [self _updateContentScale];
}

- (void)viewDidMoveToWindow {
  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(scaleDidChange:)
                                               name:@"NSWindowDidChangeBackingPropertiesNotification"
                                             object:[self window]];

  [self _updateContentScale];
}

- (void)removeFromSuperview {
  [super removeFromSuperview];
  [[NSNotificationCenter defaultCenter] removeObserver:self
                                                  name:@"NSWindowDidChangeBackingPropertiesNotification"
                                                object:[self window]];
}
@end
