#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

template<typename Tp>
static constexpr auto succeed(Tp res, input_t rem) {
  return result { success { res }, rem };
}

static_assert(!any_char()(""));
static_assert(any_char()("a") == succeed('a', ""));
static_assert(any_char()("xy") == succeed('x', "y"));

static_assert(!match('A')(""));
static_assert(!match('A')("_"));
static_assert(match('A')("A") == succeed('A', ""));
static_assert(match('A')("AB") == succeed('A', "B"));

static_assert(!match("ABC")(""));
static_assert(!match("ABC")("AB"));
static_assert(!match("ABC")("AABC"));
static_assert(match("ABC")("ABC") == succeed(input_t { "ABC" }, ""));
static_assert(match("ABC")("ABCD") == succeed(input_t { "ABC" }, "D"));

static_assert(!match_any_of("ABC")(""));
static_assert(!match_any_of("ABC")("D"));
static_assert(match_any_of("ABC")("A") == succeed('A', ""));
static_assert(match_any_of("ABC")("B") == succeed('B', ""));
static_assert(match_any_of("ABC")("C") == succeed('C', ""));
static_assert(match_any_of("ABC")("ABC") == succeed('A', "BC"));
static_assert(match_any_of("ABC")("BC") == succeed('B', "C"));

static_assert(!match_range('a', 'z')(""));
static_assert(!match_range('a', 'z')("0"));
static_assert(match_range('a', 'z')("a") == succeed('a', ""));
static_assert(match_range('a', 'z')("d") == succeed('d', ""));
static_assert(match_range('a', 'z')("z") == succeed('z', ""));
static_assert(match_range('a', 'z')("zaza") == succeed('z', "aza"));

static_assert(!match_none_of("ABC")(""));
static_assert(!match_none_of("ABC")("A"));
static_assert(!match_none_of("ABC")("B"));
static_assert(!match_none_of("ABC")("C"));
static_assert(match_none_of("ABC")("D") == succeed('D', ""));
static_assert(match_none_of("ABC")("EF") == succeed('E', "F"));

static_assert(eof()("") == succeed(nil {}, ""));
static_assert(!eof()("A"));
