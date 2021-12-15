#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/constants.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

static_assert(!fail<char>("")(""));
static_assert(fail<char>("msg")("rem") == result { failure<char> { "msg" }, "rem" });
static_assert((match('X') | fail<char>("msg"))("rem") == result { failure<char> { "msg" }, "rem" });
static_assert((match('r') & fail<char>("msg"))("rem") == result { failure<char> { "msg" }, "em" });

static_assert(constant<int>(3)("") == result { success { 3 }, "" });
static_assert(constant<int>(4)("abc") == result { success { 4 }, "abc" });

static constexpr auto fn(int i) {
  return [i]() {
    return i;
  };
}
static_assert(producer(fn(3))("") == result { success { 3 }, "" });
static_assert(producer(fn(4))("abc") == result { success { 4 }, "abc" });

static_assert(producer_of<int>(3)("") == result { success { 3 }, "" });
static_assert(producer_of<int>(4)("abc") == result { success { 4 }, "abc" });
