#pragma once

#include "m4c0/parser/result.hpp"

namespace m4c0::parser {
  template<typename T>
  static constexpr auto fail(input_t msg) noexcept {
    return [msg](input_t in) noexcept {
      return result { failure<T> { msg }, in };
    };
  }
}
