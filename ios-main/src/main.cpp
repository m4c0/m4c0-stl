#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/middleware.hpp"

extern "C" int UIApplicationMain(int argc, char ** argv, void * app_class_name, void * delegate_class_name);

int main(int argc, char ** argv) {
  m4c0::objc::autorelease_pool pool;

  void * obj = m4c0::objc::middleware::instance().create_for_protocol("UIApplicationDelegate");
  void * cls_name = m4c0::objc::objc_msg_send<void *>(obj, "className");

  return UIApplicationMain(argc, argv, nullptr, cls_name);
}
