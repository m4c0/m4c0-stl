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

  /// \brief Produces a constant value
  /// Requires a value that can be copied. This requirement is due to the fact a parser might be invoked multiple times.
  template<typename T>
  requires std::is_trivially_destructible_v<T>
  static constexpr auto constant(T && t) noexcept {
    return [t](input_t in) noexcept {
      return result { success { t }, in };
    };
  }

  /// \brief Produces values by calling a function
  /// Uses a function to produce a success value.
  template<typename Fn>
  requires std::is_invocable_v<Fn>
  static constexpr auto producer(Fn && fn) noexcept {
    return [fn = std::forward<Fn>(fn)](input_t in) noexcept {
      return result { success { fn() }, in };
    };
  }
}
