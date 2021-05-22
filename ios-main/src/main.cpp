#include "m4c0/ios/main.hpp"
#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_string.hpp"

extern "C" {
int UIApplicationMain(int, char **, void *, void *);
}

static m4c0::ios::delegate * g_delegate; // NOLINT

static bool finish_launch(void * self, void * /*sel*/, void * /*app*/, void * /*opts*/) {
  m4c0::objc::ns_object vc { "UIViewController", "new", false };
  m4c0::objc::ns_object view = { "MTKView", "new", false };
  m4c0::objc::objc_msg_send<void>(vc.self(), "setView:", view.self());

  m4c0::objc::ns_object main_scr { "UIScreen", "mainScreen", true };
  m4c0::objc::cg_rect frame = m4c0::objc::objc_msg_send<m4c0::objc::cg_rect>(main_scr.self(), "bounds");

  m4c0::objc::ns_object wnd { "UIWindow", "new", false };
  m4c0::objc::object_set_ivar(self, "window", wnd.self());
  m4c0::objc::objc_msg_send<void>(wnd.self(), "setFrame:", frame);
  m4c0::objc::objc_msg_send<void>(wnd.self(), "setRootViewController:", vc.self());
  m4c0::objc::objc_msg_send<void>(wnd.self(), "makeKeyAndVisible");

  g_delegate->start(view.self());
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
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
  return UIApplicationMain(argc, argv, nullptr, app_del.self());
}
