#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_application : public ns_object {
    using ns_object::ns_object;

  public:
    static ns_application shared_application();

    void set_delegate(const ns_object * d);

    void run();
  };
}
