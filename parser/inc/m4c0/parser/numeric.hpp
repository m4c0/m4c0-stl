#pragma once

#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/str.hpp"

namespace m4c0::parser {
  constexpr auto match_digit() {
    constexpr auto to_int = [](char c) {
      return c - '0';
    };
    return fmap(to_int, match_range('0', '9')) | "Expecting digit";
  }
}
