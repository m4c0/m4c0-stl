#include "m4c0/ios/main.hpp"
#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/objc/ns_string.hpp"
#include "m4c0/objc/ui_screen.hpp"
#include "m4c0/objc/ui_view_controller.hpp"
#include "m4c0/objc/ui_window.hpp"

extern "C" {
int UIApplicationMain(int, char **, void *, void *);
}

static m4c0::ios::delegate * g_delegate; // NOLINT

static bool finish_launch(void * self, void * /*sel*/, void * /*app*/, void * /*opts*/) {
  m4c0::objc::mtk_view view;

  m4c0::objc::ui_view_controller vc;
  vc.set_view(view);

  m4c0::objc::ui_window wnd;
  wnd.set_frame(m4c0::objc::ui_screen::main_screen().bounds());
  wnd.set_root_view_controller(vc);
  wnd.make_key_and_visible();

  void * wnd_r = m4c0::objc::objc_msg_send<void *>(wnd.self(), "retain");
  m4c0::objc::object_set_ivar(self, "window", wnd_r);
  g_delegate->start(&view);
  return true;
}
static void will_term(void * /*self*/, void * /*sel*/, void * /*app*/) {
  g_delegate->stop();
}

int m4c0::ios::main(int argc, char ** argv, m4c0::ios::delegate * delegate) {
  objc::autorelease_pool pool;

  // TODO: find a way to pass the delegate
  // It is harder than it looks because we can't pass instances to UIApplicationMain
  const char * app_del_cls = m4c0::objc::class_builder("NSObject")
                                 .add_id_ivar("window")
                                 .add_method("application:didFinishLaunchingWithOptions:", &finish_launch, "B@:@@")
                                 .add_method("applicationWillTerminate:", &will_term, "v@:@")
                                 .build();

  g_delegate = delegate;

  auto app_del = objc::ns_string::with_cstring_utf8(app_del_cls);
  return UIApplicationMain(argc, argv, nullptr, app_del.self());
}
