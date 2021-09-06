#pragma once

#include "m4c0/parser/result.hpp"

#include <string_view>
#include <type_traits>

namespace m4c0::parser {
  template<typename Tp, typename ResTp>
  concept is_parser = std::is_invocable_r_v<result<ResTp>, Tp, std::string_view>;
}
