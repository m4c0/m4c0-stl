#pragma once

#include "m4c0/containers/unique_array.hpp"

#include <cstdint>
#include <exception>
#include <optional>
#include <string_view>

namespace m4c0::ark::zip {
  struct cdir_meta {
    uint16_t count;
    uint32_t size;
    uint32_t offset;
  };
  struct cdir_entry {
    uint16_t flags {};
    uint16_t method {};
    uint32_t crc {};
    uint32_t compressed_size {};
    uint32_t uncompressed_size {};
    uint32_t offset {};
    containers::unique_array<uint8_t> filename {};
    containers::unique_array<uint8_t> extra {};
  };

  struct missing_eocd_error : std::exception {};
  struct truncated_eocd_error : std::exception {};
  struct multidisk_is_unsupported : std::exception {};
  struct zip64_is_unsupported : std::exception {};

  struct invalid_central_directory : std::exception {};
  struct truncated_central_directory : std::exception {};
  struct unsupported_zip_version : std::exception {};

  template<typename Exc, typename T>
  static constexpr T unwrap(std::optional<T> v) {
    if (!v) throw Exc {};
    return *v;
  }

  static constexpr bool filename_matches(const cdir_entry & cd, std::string_view filename) {
    return std::equal(filename.begin(), filename.end(), cd.filename.begin(), cd.filename.end());
  }
}
