#import "M4C0AppDelegate.h"

#if !__has_feature(objc_arc)
#error "ARC is off"
#endif

#include "main.h"

#include <objc/runtime.h>

const char * m4c0_osx_get_delegate_name() { // NOLINT
  return class_getName([M4C0AppDelegate class]);
}
