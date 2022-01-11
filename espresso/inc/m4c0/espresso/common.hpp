#pragma once

#include <optional>

namespace m4c0::espresso {
  template<typename T>
  static constexpr T unwrap(std::optional<T> v, const char * err_msg) {
    if (!v) throw std::runtime_error(err_msg);
    return *v;
  }
}
