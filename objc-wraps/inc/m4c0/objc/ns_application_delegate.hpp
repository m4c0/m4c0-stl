#pragma once

#include "m4c0/objc/ns_object.hpp"
#include "m4c0/objc/wrapper.hpp"

namespace m4c0::objc {
  class ns_application_delegate : public wrapper<ns_application_delegate, ns_object> {
  public:
    ns_application_delegate();
    virtual bool application_should_terminate_after_last_window_closed(void *) = 0;
    virtual void application_will_terminate(void *) = 0;
  };
}
