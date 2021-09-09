#pragma once

#include "m4c0/parser/result.hpp"

#include <string_view>
#include <type_traits>

namespace m4c0::parser {
  template<typename Tp>
  concept is_parser = std::is_invocable_v<Tp, std::string_view>;

  template<typename Fn, typename P>
  concept accepts = std::is_invocable_v<Fn, typename std::invoke_result_t<P, std::string_view>::type>;

  template<typename Fn, typename P>
  concept cant_accept = !accepts<Fn, P>;

  template<typename P>
  concept not_a_parser = !is_parser<P>;
}
