#pragma once

#include "m4c0/espresso/base_parsing.hpp"

namespace m4c0::espresso {
  constexpr const auto jclass_magic_number = 0xCAFEBABE;
  constexpr const auto latest_supported_version = 0x37; // Java SE 11
  constexpr const auto first_supported_version = 0x2D;  // JDK 1.1

  [[nodiscard]] static constexpr auto is_supported_major_version(uint16_t n) noexcept {
    return n >= first_supported_version && n <= latest_supported_version;
  }

  [[nodiscard]] static constexpr auto magic() noexcept {
    return match_u32(jclass_magic_number) | "Invalid magic number";
  }
  [[nodiscard]] static constexpr auto minor_version() noexcept {
    return u16();
  }
  [[nodiscard]] static constexpr auto major_version() noexcept {
    return (u16() && is_supported_major_version) | "Invalid/unknown major version";
  }
  [[nodiscard]] static constexpr auto magic_version() noexcept {
    return magic() & minor_version() & major_version();
  }
}
