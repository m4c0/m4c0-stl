#include "m4c0/ios/main.hpp"
#include "m4c0/objc/autorelease_pool.hpp"

#include <CoreFoundation/CoreFoundation.h>

extern "C" {
#include "main.h"
int UIApplicationMain(int, char **, CFStringRef, CFStringRef);
}

static m4c0::ios::delegate * g_delegate; // NOLINT

void m4c0_ios_main_start(void * view) {
  g_delegate->start(view);
}
void m4c0_ios_main_stop() {
  g_delegate->stop();
}

int m4c0::ios::main(int argc, char ** argv, m4c0::ios::delegate * delegate) {
  objc::autorelease_pool pool;

  g_delegate = delegate;

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
  return UIApplicationMain(argc, argv, nullptr, CFSTR("M4C0AppDelegate"));
}
