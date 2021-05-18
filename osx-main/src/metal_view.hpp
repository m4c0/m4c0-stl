#pragma once

#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/mtk_view.hpp"

static constexpr const char * cpp_ivar_name = "m4c0_$$_cpp";

static const char * get_view_name() {
  static constexpr const char * view_name = "M4C0_$$_osx_main_view";

  static class register_class {
  public:
    register_class() {
      auto * cls = objc_allocateClassPair(objc_getClass("MTKView"), view_name, 0);
      class_addIvar(cls, cpp_ivar_name, sizeof(void *), alignof(void *), "@");
      objc_registerClassPair(cls);
    }
  } r;

  return view_name;
}

namespace m4c0::osx::details {
  class view : public m4c0::objc::mtk_view {
  public:
    view() : mtk_view(get_view_name()) {
      object_set_ivar(self(), cpp_ivar_name, this);
    }
  };
}
