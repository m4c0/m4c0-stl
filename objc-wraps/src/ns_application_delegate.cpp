#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/ns_application_delegate.hpp"

using del = m4c0::objc::ns_application_delegate;
static constexpr const char * cpp_ivar_name = m4c0::objc::delegated_class_builder<del>::cpp_ivar_name;

static const char * get_delegate_name() {
  static const char * delegate_name =
      m4c0::objc::delegated_class_builder<del>("NSObject")
          .add_method<&del::application_should_terminate_after_last_window_closed>(
              "applicationShouldTerminateAfterLastWindowClosed:",
              "B@:@")
          .add_method<&del::application_will_terminate>("applicationWillTerminate:", "v@:@")
          .build();

  return delegate_name;
}
m4c0::objc::ns_application_delegate::ns_application_delegate() : ns_object(get_delegate_name()) {
  object_set_ivar(self(), cpp_ivar_name, this);
}
