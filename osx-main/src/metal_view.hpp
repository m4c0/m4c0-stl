#pragma once

#include "m4c0/objc/ca_metal_layer.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"
#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/objc/ns_application.hpp"
#include "m4c0/objc/ns_notification_center.hpp"
#include "m4c0/objc/ns_window.hpp"
#include "m4c0/objc/wrapper.hpp"

namespace m4c0::osx::details {
  class view : public objc::wrapper<view, objc::mtk_view> {
    static constexpr const auto notif = "NSWindowDidChangeBackingPropertiesNotification";

    void did_move_to_window() {
      auto wnd = window();
      objc::ns_notification_center::default_center().add_observer(this, "scaleDidChange:", notif, &wnd);
      scale_did_change(nullptr);
    }
    void remove_from_superview() {
      objc::objc_msg_send_super<void>(self(), "removeFromSuperview");

      auto wnd = window();
      objc::ns_notification_center::default_center().remove_observer(this, notif, &wnd);
    }

    // http://smokyonion.github.io/blog/2012/11/11/how-to-make-your-mac-apps-retina-ready/
    void scale_did_change(void * /*notif*/) {
      auto wnd = window();
      if (!wnd) wnd = objc::ns_application::shared_application().main_window();
      if (!wnd) return;

      layer().set_contents_scale(wnd.backing_scale_factor());
    }

  public:
    view()
      : wrapper([] {
        return objc::delegated_class_builder<view>("MTKView")
            .add_method<&view::did_move_to_window>("viewDidMoveToWindow", "v@:")
            .add_method<&view::remove_from_superview>("removeFromSuperview", "v@:")
            .add_method<&view::scale_did_change>("scaleDidChange:", "v@:@");
      }) {
    }
  };
}
