#pragma once

#include <cstdint>
#include <exception>
#include <optional>

namespace m4c0::ark::zip {
  struct cdir_meta {
    uint16_t count;
    uint32_t size;
    uint32_t offset;
  };

  struct missing_eocd_error : std::exception {};
  struct truncated_eocd_error : std::exception {};
  struct multidisk_is_unsupported : std::exception {};
  struct zip64_is_unsupported : std::exception {};

  template<typename Exc, typename T>
  static constexpr T unwrap(std::optional<T> v) {
    if (!v) throw Exc {};
    return *v;
  }
}
