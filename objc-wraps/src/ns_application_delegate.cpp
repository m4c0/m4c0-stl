#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_application_delegate.hpp"

static constexpr const char * cpp_ivar_name = "m4c0_$$_cpp";

static const char * get_delegate_name() {
  static constexpr const char * delegate_name = "M4C0_$$_AppDelegate";
  static class register_app_delegate {
    static auto * get_delegate(void * self) {
      return m4c0::objc::object_get_ivar<m4c0::objc::ns_application_delegate *>(self, cpp_ivar_name);
    }
    static BOOL astalwc(void * self, void * /*sel*/, void * /*sender*/) {
      return get_delegate(self)->application_should_terminate_after_last_window_closed() ? YES : NO;
    }
    static void awt(void * self, void * /*sel*/, void * /*sender*/) {
      get_delegate(self)->application_will_terminate();
    }

  public:
    register_app_delegate() {
      Class cls = objc_allocateClassPair(objc_getClass("NSObject"), delegate_name, 0);
      class_addIvar(cls, cpp_ivar_name, sizeof(void *), alignof(void *), "@");
      class_addMethod(
          cls,
          sel_getUid("applicationShouldTerminateAfterLastWindowClosed:"),
          m4c0::objc::to_imp(astalwc),
          "B@:@");
      class_addMethod(cls, sel_getUid("applicationWillTerminate:"), m4c0::objc::to_imp(awt), "v@:@");
      objc_registerClassPair(cls);
    }
  } r;
  return delegate_name;
}
m4c0::objc::ns_application_delegate::ns_application_delegate() : ns_object(get_delegate_name()) {
  object_set_ivar(self(), cpp_ivar_name, this);
}
