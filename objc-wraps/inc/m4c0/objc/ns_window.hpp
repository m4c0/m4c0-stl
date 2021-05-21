#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_object.hpp"
#include "m4c0/objc/ns_window_collection_behavior.hpp"
#include "m4c0/objc/ns_window_style_mask.hpp"

namespace m4c0::objc {
  class ns_window : public ns_object {
  public:
    ns_window() : ns_object("NSWindow") {
    }
    explicit ns_window(void * obj) : ns_object(obj) {
    }

    [[nodiscard]] cg_float backing_scale_factor();
    [[nodiscard]] ns_object content_view();
    [[nodiscard]] cg_point mouse_location_outside_of_event_stream();

    void set_accepts_mouse_moved_events(bool accepts);
    void set_collection_behavior(ns_window_collection_behavior cb);
    void set_content_view(const ns_object & view);
    void set_frame(cg_rect frame, bool display);
    void set_style_mask(ns_window_style_mask mask);
    void set_title(const char * title);

    void center();
    void make_key_and_order_front(); // sender=self
  };
}
