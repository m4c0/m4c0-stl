#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/ns_application_delegate.hpp"

static constexpr const char * cpp_ivar_name = "m4c0_$$_cpp";

static auto * get_delegate(void * self) {
  return m4c0::objc::object_get_ivar<m4c0::objc::ns_application_delegate *>(self, cpp_ivar_name);
}
static BOOL astalwc(void * self, void * /*sel*/, void * /*sender*/) {
  return get_delegate(self)->application_should_terminate_after_last_window_closed() ? YES : NO;
}
static void awt(void * self, void * /*sel*/, void * /*sender*/) {
  get_delegate(self)->application_will_terminate();
}
static const char * get_delegate_name() {
  static const char * delegate_name =
      m4c0::objc::class_builder("NSObject")
          .add_ptr_ivar(cpp_ivar_name)
          .add_method("applicationShouldTerminateAfterLastWindowClosed:", astalwc, "B@:@")
          .add_method("applicationWillTerminate:", awt, "v@:@")
          .build();

  return delegate_name;
}
m4c0::objc::ns_application_delegate::ns_application_delegate() : ns_object(get_delegate_name()) {
  object_set_ivar(self(), cpp_ivar_name, this);
}
