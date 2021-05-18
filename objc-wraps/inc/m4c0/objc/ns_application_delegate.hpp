#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_application_delegate : public ns_object {
  public:
    ns_application_delegate();

    virtual bool application_should_terminate_after_last_window_closed() = 0;
    virtual void application_will_terminate() = 0;
  };
}
