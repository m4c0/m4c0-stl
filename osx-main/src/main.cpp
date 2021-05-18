#include "app_delegate.hpp"
#include "apple_menu.hpp"
#include "key_window.hpp"
#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_bundle.hpp"
#include "m4c0/osx/main.hpp"

#include <objc/runtime.h>
#include <string>

int m4c0::osx::main(int /*argc*/, char ** /*argv*/, m4c0::osx::delegate * d) {
  objc::autorelease_pool pool;

  auto app = objc::ns_application::shared_application();
  auto bundle_name = objc::ns_bundle::main_bundle().bundle_name();

  const char * title = (bundle_name.self() == nullptr) ? "App" : bundle_name.c_string_using_utf8();

  setup_apple_menu(&app, title);
  auto wnd = setup_window(title);
  d->start(wnd.content_view().self());

  details::app_delegate app_del { d };

  app.set_delegate(&app_del);

  app.activate_ignoring_other_apps(true);
  app.run();

  return 0;
}
