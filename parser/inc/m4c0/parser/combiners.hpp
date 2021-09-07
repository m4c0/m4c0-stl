#pragma once

#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/traits.hpp"

namespace m4c0::parser {
  template<typename Fn, typename P>
  requires is_parser<P> && accepts<Fn, P>
  constexpr auto fmap(Fn && fn, P && p) noexcept {
    return [fn, p](std::string_view in) {
      return p(in).map(fn);
    };
  }

  template<typename P>
  requires is_parser<P>
  constexpr auto operator|(P && p, result_of_t<P> otherwise) noexcept {
    return [p, otherwise](std::string_view in) {
      const auto r = p(in);
      return r ? r : otherwise;
    };
  }

  template<typename P>
  requires is_parser<P>
  constexpr auto operator|(P && p, std::string_view msg) noexcept {
    return p | failure<type_of_t<P>>(msg);
  }
}
