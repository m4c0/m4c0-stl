#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/result.hpp"

using namespace m4c0::parser;

template<typename Tp>
static constexpr result<Tp> dummy(input_t in) {
  return { failure<Tp>(""), in };
}

template<typename P>
requires is_parser<P>
static constexpr bool test(P /*p*/) {
  return true;
}
static_assert(test(dummy<char>));
static_assert(test(dummy<int>));

template<typename P, typename Fn>
requires is_parser<P> && accepts<Fn, P>
static constexpr bool test_accept(Fn /*fn*/, P /*p*/) {
  return true;
}
static constexpr int to_int(char /*c*/) {
  return 0;
}
static_assert(test_accept(to_int, dummy<char>));
