#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_menu.hpp"
#include "m4c0/objc/ns_menu_item.hpp"
#include "m4c0/objc/ns_object.hpp"
#include "m4c0/osx/main.hpp"

extern "C" {
#include "main.h"
}

#include <objc/runtime.h>

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

  objc::ns_menu bar;
  objc::ns_menu_item app_item;
  objc::ns_menu app_menu;

  app_menu.add_item(objc::ns_menu_item::with_title_action_key("Quit", "terminate:", "q"));

  app_item.set_submenu(&app_menu);
  bar.add_item(app_item);
  app.set_main_menu(&bar);

  objc::ns_object app_del { m4c0_osx_get_delegate_name() };
  app.set_delegate(&app_del);

  app.run();

  return 0;
}
