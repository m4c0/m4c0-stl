#include "m4c0/ios/main.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/inject.hpp"
#include "m4c0/objc/middleware.hpp"

#include <CoreGraphics/CoreGraphics.h>

using m4c0::objc::objc_msg_send;

// TODO: Find a way to keep this in `self`
static void * view_controller;
static void * view_delegate;
static void * window;

static void * create_obj(const char * cls_name, const char * msg_name) {
  void * cls = objc_getClass(cls_name);
  return objc_msg_send<void *>(cls, msg_name);
}

static void * create_view() {
  void * view = create_obj("MTKView", "new");
  view_delegate = m4c0::objc::middleware::instance().create_for_protocol("MTKViewDelegate");
  objc_msg_send<void>(view_delegate, "retain");
  objc_msg_send<void>(view, "setDelegate:", view_delegate);
  return view;
}

static void * create_view_controller() {
  view_controller = create_obj("UIViewController", "new");
  objc_msg_send<void>(view_controller, "setView:", create_view());
  return objc_msg_send<void *>(view_controller, "retain");
}

static void * create_window() {
  void * main_scr = create_obj("UIScreen", "mainScreen");
  CGRect wnd_bounds = objc_msg_send<CGRect>(main_scr, "bounds");

  void * wnd = create_obj("UIWindow", "alloc");
  wnd = objc_msg_send<void *>(wnd, "initWithFrame:", wnd_bounds);
  objc_msg_send<void>(wnd, "setRootViewController:", create_view_controller());
  objc_msg_send<void>(wnd, "makeKeyAndVisible");
  return objc_msg_send<void *>(wnd, "retain");
}

static BOOL app_did_finish_launching(void * self) {
  window = create_window();
  return YES;
}
m4c0::ios::inject_app_did_finish_launch_with_options::inject_app_did_finish_launch_with_options()
  : m4c0::objc::static_inject("application:didFinishLaunchingWithOptions:", &app_did_finish_launching) {
}
