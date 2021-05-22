#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_object.hpp"

#include <type_traits>

namespace m4c0::objc {
  class ca_metal_layer;
  class ns_window;
  class ui_window;

  class mtk_view : public ns_object {
    using window_t = std::conditional_t<TARGET_OS_OSX, ns_window, ui_window>;

  protected:
    explicit mtk_view(const char * cls_name) : ns_object(cls_name) {
    }

  public:
    mtk_view() : ns_object("MTKView") {
    }

    [[nodiscard]] cg_rect bounds() const;
    [[nodiscard]] ca_metal_layer layer() const;
    [[nodiscard]] window_t window() const;
  };
}
