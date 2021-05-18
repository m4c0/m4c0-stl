#include "apple_menu.hpp"
#include "key_window.hpp"
#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_application_delegate.hpp"
#include "m4c0/objc/ns_bundle.hpp"
#include "m4c0/objc/ns_object.hpp"
#include "m4c0/osx/main.hpp"

extern "C" {
#include "main.h"
}

#include <objc/runtime.h>
#include <string>

static m4c0::osx::delegate * g_delegate; // NOLINT

class my_delegate : public m4c0::objc::ns_application_delegate {
public:
  bool application_should_terminate_after_last_window_closed() override {
    return true;
  }
  void application_will_terminate() override {
    g_delegate->stop();
  }
};

int m4c0::osx::main(int /*argc*/, char ** /*argv*/, m4c0::osx::delegate * delegate) {
  objc::autorelease_pool pool;

  g_delegate = delegate;

  auto app = objc::ns_application::shared_application();
  auto bundle_name = objc::ns_bundle::main_bundle().bundle_name();

  const char * title = (bundle_name.self() == nullptr) ? "App" : bundle_name.c_string_using_utf8();

  setup_apple_menu(&app, title);
  auto wnd = setup_window(title);
  delegate->start(wnd.content_view().self());

  my_delegate app_del;
  app.set_delegate(&app_del);

  app.activate_ignoring_other_apps(true);
  app.run();

  return 0;
}
