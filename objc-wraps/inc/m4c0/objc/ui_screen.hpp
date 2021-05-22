#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ui_screen : public ns_object {
    using ns_object::ns_object;

  public:
    [[nodiscard]] cg_rect bounds() const {
      return get<cg_rect>("bounds");
    }
    [[nodiscard]] static ui_screen main_screen() {
      return ui_screen { "UIScreen", "mainScreen", true };
    }
  };
}
