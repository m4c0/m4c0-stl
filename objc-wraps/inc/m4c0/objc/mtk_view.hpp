#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class mtk_view : public ns_object {
  public:
    mtk_view() : ns_object("MTKView") {
    }
  };
}
