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
}
