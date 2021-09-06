#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/result.hpp"

using namespace m4c0::parser;

template<typename ResTp, typename P>
requires is_parser<P, ResTp>
static constexpr bool test(P /*p*/) {
  return true;
}
static_assert(test<char>([](std::string_view /*in*/) -> result<char> {
  return failure<char>("");
}));
static_assert(test<int>([](std::string_view /*in*/) -> result<int> {
  return failure<int>("");
}));
