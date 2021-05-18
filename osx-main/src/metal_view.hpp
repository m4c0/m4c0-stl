#pragma once

#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/mtk_view.hpp"

static constexpr const char * cpp_ivar_name = "m4c0_$$_cpp";

static const char * get_view_name() {
  static const auto * cls = m4c0::objc::class_builder("MTKView").add_ptr_ivar(cpp_ivar_name).build();
  return cls;
}

namespace m4c0::osx::details {
  class view : public m4c0::objc::mtk_view {
  public:
    view() : mtk_view(get_view_name()) {
      object_set_ivar(self(), cpp_ivar_name, this);
    }
  };
}
