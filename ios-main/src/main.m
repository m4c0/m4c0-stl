#include "main.h"

#import <UIKit/UIKit.h>

void objc_main(int argc, char ** argv, const char * delegate) {
  @autoreleasepool {
    Protocol * ui_application_delegate = @protocol(UIApplicationDelegate);
    NSString * s = [NSString stringWithUTF8String:delegate];
    UIApplicationMain(argc, argv, nil, s);
  }
}
