#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_window.hpp"
#include "metal_view.hpp"

namespace m4c0::osx::details {
  class window : public objc::ns_window {
    view m_view {};

  public:
    explicit window(const char * title) : ns_window() {
      using namespace m4c0::objc;

      constexpr const auto window_width = 800;
      constexpr const auto window_height = 600;

      set_content_view(m_view);
      set_accepts_mouse_moved_events(true);
      set_title(title);
      set_style_mask(
          ns_window_style_mask::titled | ns_window_style_mask::closable | ns_window_style_mask::miniaturizable
          | ns_window_style_mask::resizable);
      set_collection_behavior(ns_window_collection_behavior::full_screen_primary);
      set_frame(cg_rect { {}, { window_width, window_height } }, true);

      center();
      make_key_and_order_front();
    }

    [[nodiscard]] constexpr const auto * content_view() {
      return &m_view;
    }
  };
}
