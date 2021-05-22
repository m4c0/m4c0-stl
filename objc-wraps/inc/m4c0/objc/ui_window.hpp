#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_object.hpp"
#include "m4c0/objc/ui_view_controller.hpp"

namespace m4c0::objc {
  class ui_window : public ns_object {
  public:
    ui_window() : ns_object("UIWindow") {
    }
    explicit ui_window(void * obj) : ns_object(obj) {
    }

    void set_frame(cg_rect frame) const {
      set("setFrame:", frame);
    }
    void set_root_view_controller(const ui_view_controller & o) const {
      set<ns_object>("setRootViewController:", o);
    }

    void make_key_and_visible() const {
      send("makeKeyAndVisible");
    }
  };
}
