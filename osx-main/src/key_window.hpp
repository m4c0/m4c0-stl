#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_window.hpp"

extern "C" {
#include "main.h"
}

[[nodiscard]] static m4c0::objc::ns_window setup_window(const char * title) {
  using namespace m4c0::objc;

  constexpr const auto window_width = 800;
  constexpr const auto window_height = 600;

  ns_window wnd;
  wnd.set_content_view(ns_object(m4c0_osx_get_view_name()));
  wnd.set_accepts_mouse_moved_events(true);
  wnd.set_title(title);
  wnd.set_style_mask(
      ns_window_style_mask::titled | ns_window_style_mask::closable | ns_window_style_mask::miniaturizable
      | ns_window_style_mask::resizable);
  wnd.set_collection_behavior(ns_window_collection_behavior::full_screen_primary);
  wnd.set_frame(cg_rect { {}, { window_width, window_height } }, true);

  wnd.center();
  wnd.make_key_and_order_front();
  return wnd;
}
