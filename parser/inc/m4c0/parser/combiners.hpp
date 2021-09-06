#pragma once

#include "m4c0/parser/concept.hpp"

namespace m4c0::parser {
  template<typename Fn, typename P>
  requires is_parser<P> && accepts<Fn, P>
  constexpr auto fmap(Fn && fn, P && p) noexcept {
    return [fn, p](std::string_view in) {
      return p(in).map(fn);
    };
  }
}
