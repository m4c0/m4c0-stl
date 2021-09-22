#pragma once

#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/result.hpp"

namespace m4c0::parser {
  template<typename>
  struct token {
    input_t value;
  };
  template<typename T>
  static constexpr bool operator==(const token<T> & a, const token<T> & b) noexcept {
    return a.value == b.value;
  }

  template<typename T, typename P>
  requires is_parser<P>
  static constexpr auto tokenise(P && p) noexcept {
    return [p](input_t in) noexcept -> result<token<T>> {
      return p(in) & [in](auto /*r*/, input_t rem) noexcept -> result<token<T>> {
        const auto substr = rem.empty() ? in : in.up_to(rem);
        return { success { token<T> { substr } }, rem };
      };
    };
  }
}
