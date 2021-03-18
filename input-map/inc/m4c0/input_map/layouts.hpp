#pragma once

#include "m4c0/function.hpp"

namespace m4c0::input_map::layout {
  namespace details {
    using axis_callback = function<void(float)>;
    using button_callback = function<void(bool)>;

    struct pad {
      axis_callback horizontal;
      axis_callback vertical;
    };

    struct pad_with_button : public pad {
      button_callback center;
    };

    struct quad_button {
      button_callback left;
      button_callback top;
      button_callback right;
      button_callback bottom;
    };
  }

  struct base_controller {
    details::pad_with_button lpad;
    details::quad_button dpad;

    details::pad_with_button rpad;
    details::quad_button buttons;
  };
  struct xbox : public base_controller {};
}
