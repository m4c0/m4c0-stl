#pragma once

#include "m4c0/objc/ns_application_delegate.hpp"
#include "m4c0/osx/main.hpp"

namespace m4c0::osx::details {
  class app_delegate : public m4c0::objc::ns_application_delegate {
    delegate * m_delegate;

  public:
    explicit app_delegate(delegate * d) : ns_application_delegate(), m_delegate(d) {
    }
    bool application_should_terminate_after_last_window_closed(void * /*app*/) override {
      return true;
    }
    void application_will_terminate(void * /*not*/) override {
      m_delegate->stop();
    }
  };
}
