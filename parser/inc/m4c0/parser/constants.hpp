#pragma once

#include "m4c0/parser/result.hpp"

#include <type_traits>

namespace m4c0::parser {
  template<typename T>
  static constexpr auto fail(input_t msg) noexcept {
    return [msg](input_t in) noexcept {
      return result { failure<T> { msg }, in };
    };
  }

  template<typename T>
  requires std::is_trivially_destructible_v<T>
  static constexpr auto constant(T && t) noexcept {
    return [t](input_t in) noexcept {
      return result { success { t }, in };
    };
  }
}
