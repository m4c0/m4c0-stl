#include "apple_menu.hpp"
#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_bundle.hpp"
#include "m4c0/objc/ns_object.hpp"
#include "m4c0/osx/main.hpp"

extern "C" {
#include "main.h"
}

#include <objc/runtime.h>
#include <string>

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

  auto app = objc::ns_application::shared_application();
  auto title = objc::ns_bundle::main_bundle().bundle_name();
  if (title.self() == nullptr) title = objc::ns_string::with_cstring_utf8("App");

  setup_apple_menu(&app, title.c_string_using_utf8());

  objc::ns_object app_del { m4c0_osx_get_delegate_name() };
  app.set_delegate(&app_del);

  app.run();

  return 0;
}
