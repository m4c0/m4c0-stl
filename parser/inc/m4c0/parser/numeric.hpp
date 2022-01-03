#pragma once

#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

namespace m4c0::parser {
  [[nodiscard]] constexpr auto match_digit() noexcept {
    constexpr auto to_int = [](char c) noexcept {
      return c - '0';
    };
    return match_range('0', '9') & to_int | "Expecting digit";
  }
  [[nodiscard]] constexpr auto match_u32() noexcept {
    class digit {
      unsigned m_v { 0 };

      [[nodiscard]] constexpr explicit digit(unsigned v) : m_v { v } {
      }

    public:
      [[nodiscard]] constexpr digit() = default;

      [[nodiscard]] constexpr auto operator+(int i) const noexcept {
        constexpr const auto radix = 10;
        return digit { m_v * radix + i };
      }

      [[nodiscard]] constexpr auto value() const noexcept {
        return m_v;
      }
    };

    return at_least_one(match_digit(), digit {}) & &digit::value;
  }
  [[nodiscard]] constexpr auto match_s32() noexcept {
    return combine(match('-') & -1 | 1, match_u32(), [](int s, unsigned m) noexcept -> int {
      return s * static_cast<int>(m);
    });
  }
}
