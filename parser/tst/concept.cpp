#include "m4c0/parser/concept.hpp"
#include "m4c0/parser/result.hpp"

using namespace m4c0::parser;

template<typename Tp>
static constexpr result<Tp> iam_parser(input_t in) {
  return { failure<Tp>(""), in };
}
static constexpr input_t iam_groo(input_t in) {
  return in;
}

template<typename P>
static constexpr bool test(P /*p*/) {
  return is_parser<P>;
}
static_assert(test(iam_parser<char>));
static_assert(test(iam_parser<int>));
static_assert(!test(iam_groo));

template<typename P, typename Fn>
static constexpr bool test_accept(Fn /*fn*/, P /*p*/) {
  return is_parser<P> && accepts<Fn, P>;
}
static constexpr int to_int(char /*c*/) {
  return 0;
}
static_assert(test_accept(to_int, iam_parser<char>));
static_assert(!test_accept(to_int, iam_groo));
