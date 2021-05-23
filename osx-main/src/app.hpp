#pragma once

#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/osx/main.hpp"

namespace m4c0::osx {
  class app : public objc::ns_application {
    using objc::ns_application::ns_application;

    static const char * class_name() {
      static const char * cls_name = objc::delegated_class_builder<app>("NSApplication")
                                         .add_method<&app::send_event>("sendEvent:", "v@:@")
                                         .build();
      return cls_name;
    }

    void send_event(void * e) {
      auto nse = objc::ns_event(e);
      m_delegate->on_event(&nse);
      objc::objc_msg_send_super<void>("NSApplication", self(), "sendEvent:", e);
    }

    delegate * m_delegate;

  public:
    explicit app(delegate * d) : ns_application(class_name(), "sharedApplication", true), m_delegate(d) {
      objc::delegated_class_builder<app>::set_ivar(self(), this);
    }
  };
}
