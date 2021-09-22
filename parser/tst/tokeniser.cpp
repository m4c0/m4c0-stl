#include "m4c0/parser/str.hpp"
#include "m4c0/parser/tokeniser.hpp"

using namespace m4c0::parser;

template<typename T>
static constexpr auto succeed(input_t res, input_t rem) {
  return result { success { token<T> { res } }, rem };
}

struct my_token {};
static_assert(!tokenise<my_token>(match('X'))(""));
static_assert(!tokenise<my_token>(match('X'))("A"));
static_assert(tokenise<my_token>(match('X'))("X") == succeed<my_token>("X", ""));
static_assert(tokenise<my_token>(match('X'))("XX") == succeed<my_token>("X", "X"));
static_assert(tokenise<my_token>(match('X'))("Xx") == succeed<my_token>("X", "x"));
