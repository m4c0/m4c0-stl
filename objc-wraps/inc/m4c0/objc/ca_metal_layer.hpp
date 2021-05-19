#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ca_metal_layer : public ns_object {
  public:
    explicit ca_metal_layer(void * o) : ns_object(o) {
    }

    void set_contents_scale(cg_float scale);
  };
}
