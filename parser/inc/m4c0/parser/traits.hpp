#pragma once

#include "m4c0/parser/concept.hpp"

namespace m4c0::parser {
  template<typename P>
  requires is_parser<P>
  using result_of_t = std::invoke_result_t<P, input_t>;

  template<typename P>
  requires is_parser<P>
  using type_of_t = typename result_of_t<P>::type;

  template<typename A, typename B>
  struct nothrows : std::false_type {};

  template<is_nothrow_parser A, is_nothrow_parser B>
  struct nothrows<A, B> : std::true_type {};

  template<not_a_parser Fn, is_nothrow_parser P>
  requires accepts_nothrow<Fn, P>
  struct nothrows<Fn, P> : std::true_type {
  };

  template<typename A, typename B>
  static constexpr const auto nothrows_v = nothrows<A, B>::value;
}
