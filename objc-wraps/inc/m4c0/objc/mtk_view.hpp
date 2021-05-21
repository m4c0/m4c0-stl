#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ca_metal_layer;
  class ns_window;

  class mtk_view : public ns_object {
  protected:
    explicit mtk_view(const char * cls_name) : ns_object(cls_name) {
    }

  public:
    mtk_view() : ns_object("MTKView") {
    }

    [[nodiscard]] cg_rect bounds() const;
    [[nodiscard]] ca_metal_layer layer() const;
    [[nodiscard]] ns_window window() const;
  };
}
