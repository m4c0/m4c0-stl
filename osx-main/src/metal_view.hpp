#pragma once

#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/objc/wrapper.hpp"

namespace m4c0::osx::details {
  class view : public objc::wrapper<view, objc::mtk_view> {
    void did_move_to_window() {
    }
    void remove_from_superview() {
    }

    void scale_did_change(void * /*notif*/) {
    }

  public:
    view()
      : wrapper([] {
        return objc::delegated_class_builder<view>("MTKView")
            .add_method<&view::did_move_to_window>("viewDidMoveToWindow", "v@:")
            .add_method<&view::remove_from_superview>("removeFromSuperview", "v@:")
            .add_method<&view::scale_did_change>("scaleDidChange", "v@:@");
      }) {
    }
  };
}
