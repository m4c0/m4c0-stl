#pragma once

namespace m4c0::objc {
  enum class ns_event_type : unsigned {
    mouse_left_down = 1,
    mouse_left_up = 2,
    mouse_right_down = 3,
    mouse_right_up = 4,
    mouse_moved = 5,
    mouse_left_dragged = 6,
    mouse_right_dragged = 7,
    mouse_enter = 8,
    mouse_exit = 9,
  };
}
