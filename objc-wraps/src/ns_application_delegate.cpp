#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/ns_application_delegate.hpp"

using del = m4c0::objc::ns_application_delegate;

m4c0::objc::ns_application_delegate::ns_application_delegate()
  : wrapper([] {
    return m4c0::objc::delegated_class_builder<del>("NSObject")
        .add_method<&del::application_should_terminate_after_last_window_closed>(
            "applicationShouldTerminateAfterLastWindowClosed:",
            "B@:@")
        .add_method<&del::application_will_terminate>("applicationWillTerminate:", "v@:@");
  }) {
}
