#include "m4c0/parser/traits.hpp"

#include <type_traits>

using namespace m4c0::parser;

static constexpr result<char> pchar(input_t in) {
  return result { failure<char>(""), in };
}

static_assert(std::is_same_v<result<char>, result_of_t<decltype(pchar)>>);
static_assert(!std::is_same_v<result<int>, result_of_t<decltype(pchar)>>);

static_assert(std::is_same_v<char, type_of_t<decltype(pchar)>>);
static_assert(!std::is_same_v<int, type_of_t<decltype(pchar)>>);
