#pragma once

#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/objc/wrapper.hpp"

namespace m4c0::osx::details {
  class view : public objc::wrapper<view, objc::mtk_view> {
  public:
    view()
      : wrapper([] {
        return objc::delegated_class_builder<view>("MTKView");
      }) {
    }
  };
}
