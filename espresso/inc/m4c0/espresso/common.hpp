#pragma once

#include "m4c0/io/reader.hpp"

#include <optional>

namespace m4c0::espresso {
  template<typename T>
  static constexpr T unwrap(std::optional<T> v, const char * err_msg) {
    if (!v) throw std::runtime_error(err_msg);
    return *v;
  }
  static constexpr uint16_t read_u16(io::reader * r, const char * err_msg) {
    return unwrap(r->read_u16_be(), err_msg);
  }
  static constexpr uint32_t read_u32(io::reader * r, const char * err_msg) {
    return unwrap(r->read_u32_be(), err_msg);
  }
}
