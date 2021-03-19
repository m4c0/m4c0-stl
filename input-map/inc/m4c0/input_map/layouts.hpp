#pragma once

#include "m4c0/function.hpp"

namespace m4c0::input_map {
  enum class axis {
    LPAD_V,
    LPAD_H,

    RPAD_V,
    RPAD_H,
  };
  enum class buttons {
    LPAD,
    RPAD,

    DPAD_LEFT,
    DPAD_UP,
    DPAD_RIGHT,
    DPAD_DOWN,

    X,
    Y,
    A,
    B
  };
}
namespace m4c0::input_map::layout {
  namespace details {
    template<typename ValueT, auto Name>
    class control : public function<void(ValueT)> {
      using parent_t = function<void(ValueT)>;

    public:
      using parent_t::parent_t;

      [[nodiscard]] constexpr auto name() const noexcept {
        return Name;
      }
    };

    template<auto Name>
    using axis_callback = control<float, Name>;
    template<auto Name>
    using button_callback = control<bool, Name>;

    template<auto H, auto V>
    struct pad {
      axis_callback<H> horizontal;
      axis_callback<V> vertical;
    };

    template<auto H, auto V, auto B>
    struct pad_with_button : public pad<H, V> {
      button_callback<B> center;
    };

    template<auto L, auto T, auto R, auto B>
    struct quad_button {
      button_callback<L> left;
      button_callback<T> top;
      button_callback<R> right;
      button_callback<B> bottom;
    };
  }

  class device {};

  struct xbox : public device {
    details::pad_with_button<axis::LPAD_H, axis::LPAD_V, buttons::LPAD> lpad;
    details::quad_button<buttons::DPAD_LEFT, buttons::DPAD_UP, buttons::DPAD_RIGHT, buttons::DPAD_DOWN> dpad;

    details::pad_with_button<axis::RPAD_H, axis::RPAD_V, buttons::RPAD> rpad;
    details::quad_button<buttons::X, buttons::Y, buttons::B, buttons::A> buttons;
  };
}
