#pragma once

#include "m4c0/parser/result.hpp"

#include <string_view>
#include <type_traits>

namespace m4c0::parser {
  template<typename>
  struct is_parser_result : public std::false_type {};
  template<typename Tp>
  struct is_parser_result<result<Tp>> : public std::true_type {};

  template<typename Tp>
  concept is_parser = is_parser_result<std::invoke_result_t<Tp, input_t>>::value;

  template<typename Fn, typename P>
  concept accepts_directly = std::is_invocable_v<Fn, typename std::invoke_result_t<P, input_t>::type>;

  template<typename Fn, typename P>
  concept accepts_with_remainder = std::is_invocable_v<Fn, typename std::invoke_result_t<P, input_t>::type, input_t>;

  template<typename Fn, typename P>
  concept accepts = accepts_directly<Fn, P> || accepts_with_remainder<Fn, P>;

  template<typename Fn, typename P>
  concept cant_accept = !accepts<Fn, P>;

  template<typename P>
  concept not_a_parser = !is_parser<P>;
}
