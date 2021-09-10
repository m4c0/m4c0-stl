#pragma once

#include "m4c0/parser/result.hpp"

namespace m4c0::parser {
  [[nodiscard]] static constexpr auto match(char c) noexcept {
    return [c](input_t in) noexcept -> result<char> {
      if (in.empty()) return failure<char>("EOF matching char");
      if (in.at(0) != c) return failure<char>("Mismatched char");
      return success { c, in.substr(1) };
    };
  }
  [[nodiscard]] static constexpr auto match(input_t s) noexcept {
    return [s](input_t in) noexcept -> result<input_t> {
      if (in.starts_with(s)) {
        return success<input_t>(s, in.substr(s.length()));
      }
      return failure<input_t>("Mismatched string");
    };
  }
  [[nodiscard]] static constexpr auto match_any_of(input_t s) noexcept {
    return [s](input_t in) noexcept -> result<char> {
      if (in.empty()) return failure<char>("EOF matching chars");

      auto c = in.at(0);
      if (!s.contains(c)) return failure<char>("Mismatched char");

      return success<char> { c, in.substr(1) };
    };
  }
  [[nodiscard]] static constexpr auto match_range(char start, char end) noexcept {
    return [start, end](input_t in) noexcept -> result<char> {
      if (in.empty()) return failure<char>("EOF matching char range");

      auto c = in.at(0);
      if (c < start || c > end) return failure<char>("Char is not in a valid range");

      return success<char> { c, in.substr(1) };
    };
  }
}
