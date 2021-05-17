#pragma once

namespace m4c0::objc {
  enum class ns_window_style_mask : unsigned {
    borderless = 0,
    titled = 1U << 0U,
    closable = 1U << 1U,
    miniaturizable = 1U << 2U,
    resizable = 1U << 3U,
  };

  static ns_window_style_mask operator|(ns_window_style_mask lhs, ns_window_style_mask rhs) {
    return static_cast<ns_window_style_mask>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
  }
}
