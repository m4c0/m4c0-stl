#pragma once

#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

namespace m4c0::espresso {
  [[nodiscard]] static constexpr auto u8() noexcept {
    return parser::any_char() & [](char c) noexcept -> uint8_t {
      return static_cast<uint8_t>(c);
    };
  }
  [[nodiscard]] static constexpr auto u16() noexcept {
    return parser::combine(u8(), u8(), [](uint8_t a, uint8_t b) noexcept -> uint16_t {
      return (a << 8U) | b; // NOLINT
    });
  }
  [[nodiscard]] static constexpr auto u32() noexcept {
    return parser::combine(u16(), u16(), [](uint16_t a, uint16_t b) noexcept -> uint32_t {
      return (a << 16U) | b; // NOLINT
    });
  }

  [[nodiscard]] static constexpr auto match_u8(uint8_t n) noexcept {
    return u8() && [n](uint8_t o) noexcept {
      return n == o;
    };
  }
  [[nodiscard]] static constexpr auto match_u32(uint32_t n) noexcept {
    return u32() && [n](uint32_t o) noexcept {
      return n == o;
    };
  }
}
