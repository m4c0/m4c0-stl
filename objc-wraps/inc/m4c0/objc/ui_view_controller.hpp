#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ui_view_controller : public ns_object {
    static_assert(TARGET_OS_IPHONE);

  public:
    ui_view_controller() : ns_object("UIViewController", "new", false) {
    }

    void set_view(const ns_object & v) {
      set("setView:", v);
    }
  };
}
