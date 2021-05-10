#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/osx/main.hpp"

extern "C" {
#include "main.h"
}

static m4c0::osx::delegate * g_delegate; // NOLINT

void m4c0_osx_main_start(void * view) {
  g_delegate->start(view);
}
void m4c0_osx_main_stop() {
  g_delegate->stop();
}

int m4c0::osx::main(int /*argc*/, char ** /*argv*/, m4c0::osx::delegate * delegate) {
  objc::autorelease_pool pool;

  g_delegate = delegate;

  m4c0_osx_main();
  return 0;
}
