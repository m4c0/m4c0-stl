#pragma once

#include "m4c0/parser/result.hpp"

#include <string_view>

namespace m4c0::parser {
  [[nodiscard]] constexpr auto match(char c) noexcept {
    return [c](std::string_view in) -> result<char> {
      if (in.empty()) return failure<char>("EOF matching char");
      if (in.at(0) != c) return failure<char>("Mismatched char");
      return success { c, in.substr(1) };
    };
  }
  [[nodiscard]] constexpr auto match(std::string_view s) noexcept {
    using str = std::string_view;

    return [s](str in) -> result<str> {
      if (in.starts_with(s)) {
        return success<str>(s, in.substr(s.length()));
      }
      return failure<str>("Mismatched string");
    };
  }
  [[nodiscard]] constexpr auto match_any_of(std::string_view s) noexcept {
    return [s](std::string_view in) -> result<char> {
      if (in.empty()) return failure<char>("EOF matching chars");

      auto c = in[0];
      if (s.find(c) == std::string_view::npos) return failure<char>("Mismatched char");

      return success<char> { c, in.substr(1) };
    };
  }
  [[nodiscard]] constexpr auto match_range(char start, char end) noexcept {
    return [start, end](std::string_view in) -> result<char> {
      if (in.empty()) return failure<char>("EOF matching char range");

      auto c = in[0];
      if (c < start || c > end) return failure<char>("Char is not in a valid range");

      return success<char> { c, in.substr(1) };
    };
  }
}
