#pragma once

#include "m4c0/parser/concept.hpp"

namespace m4c0::parser {
  template<typename P>
  requires is_parser<P>
  using result_of_t = std::invoke_result_t<P, input_t>;

  template<typename P>
  requires is_parser<P>
  using type_of_t = typename result_of_t<P>::type;

  template<typename Fn, is_parser P>
  requires accepts<Fn, P>
  static constexpr const auto nothrows = std::is_nothrow_invocable_v<Fn, type_of_t<P>>;
}
