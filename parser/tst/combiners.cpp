#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/constants.hpp"
#include "m4c0/parser/result.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

template<typename Tp>
static constexpr auto fail(input_t msg, input_t rem) {
  return result { failure<Tp> { msg }, rem };
}
template<typename Tp>
static constexpr auto succeed(Tp res, input_t rem) {
  return result { success { res }, rem };
}

static constexpr auto fnp() {
  return match_range('A', 'Z') & [](char c) {
    return c - 'A';
  };
}
static_assert(!fnp()(""));
static_assert(!fnp()("cZ"));
static_assert(fnp()("Cz") == succeed(2, "z"));

static_assert(!(match('a') & fnp())(""));
static_assert(!(match('a') & fnp())("a"));
static_assert(!(match('a') & fnp())("bA"));
static_assert((match('a') & fnp())("aAb") == succeed(0, "b"));

static_assert((match('a') & 4)("aha") == succeed(4, "ha"));
static_assert(!(match('a') & 4)("nope"));

static constexpr auto tag_merger(char a, char b) {
  return a == '<' && b == '>';
}
static_assert(combine(match('<'), match('>'), tag_merger)("<>!") == succeed(true, "!"));

static_assert(!(match('a') + fnp())(""));
static_assert(!(match('a') + fnp())("a"));
static_assert(!(match('a') + fnp())("bA"));
static_assert((match('b') + fnp())("bCa") == succeed('b' + 2, "a"));

static_assert(!(3 + fnp())(""));
static_assert((3 + fnp())("C") == succeed(3 + 2, ""));
static_assert((3 + fnp())("CD") == succeed(3 + 2, "D"));

static_assert((match('a') | 'b')("aha") == succeed('a', "ha"));
static_assert((match('a') | 'b')("nope") == succeed('b', "nope"));

static_assert((match('a') | "nok")("aha") == succeed('a', "ha"));
static_assert((match('a') | "nok")("nope") == fail<char>("nok", "nope"));

static_assert(!(match('a') | match('c'))(""));
static_assert(!(match('a') | match('c'))("bc"));
static_assert((match('a') | match('c'))("ac") == succeed('a', "c"));
static_assert((match('a') | match('c'))("c") == succeed('c', ""));

static_assert(!skip(match('a'))(""));
static_assert(!skip(match('a'))("b"));
static_assert(skip(match('a'))("ab") == succeed(nil {}, "b"));

static_assert((match('a') + skip(match('b')))("ab") == succeed('a', ""));

struct cnt {
  unsigned c;
};
static constexpr cnt operator+(cnt a, cnt b) {
  return { (a.c << 1U) + b.c };
}
static constexpr bool operator==(cnt a, cnt b) {
  return a.c == b.c;
}
static constexpr auto cntp() {
  return match('B') & cnt { 1 };
}
struct cnt_init {
  unsigned c;
};
static constexpr cnt_init operator+(cnt_init a, cnt b) {
  return { a.c + b.c };
}
static constexpr bool operator==(cnt_init a, cnt_init b) {
  return a.c == b.c;
}

static_assert((constant(cnt_init {}) << cntp())("") == succeed(cnt_init {}, ""));
static_assert((constant(cnt_init {}) << cntp())("a") == succeed(cnt_init {}, "a"));
static_assert((constant(cnt_init {}) << cntp())("B") == succeed(cnt_init { 1 }, ""));
static_assert((constant(cnt_init {}) << cntp())("Ba") == succeed(cnt_init { 1 }, "a"));
static_assert((constant(cnt_init {}) << cntp())("BBa") == succeed(cnt_init { 2 }, "a"));
static_assert((constant(cnt_init {}) << cntp())("BBB") == succeed(cnt_init { 3 }, ""));
static_assert(!(fail<cnt_init>("") << cntp())(""));

static_assert(!at_least_one(cntp())(""));
static_assert(!at_least_one(cntp())("a"));
static_assert(at_least_one(cntp())("B") == succeed(cnt { 0b1 }, ""));
static_assert(at_least_one(cntp())("Ba") == succeed(cnt { 0b1 }, "a"));
static_assert(at_least_one(cntp())("BBa") == succeed(cnt { 0b11 }, "a"));
static_assert(at_least_one(cntp())("BBB") == succeed(cnt { 0b111 }, ""));   // NOLINT
static_assert(at_least_one(cntp())("BBBa") == succeed(cnt { 0b111 }, "a")); // NOLINT
static_assert(!at_least_one(cntp(), cnt_init {})(""));
static_assert(at_least_one(cntp(), cnt_init {})("B") == succeed(cnt_init { 1 }, "")); // NOLINT

static_assert(many(cntp())("") == succeed(cnt {}, ""));
static_assert(many(cntp())("a") == succeed(cnt {}, "a"));
static_assert(many(cntp())("B") == succeed(cnt { 0b1 }, ""));
static_assert(many(cntp())("Ba") == succeed(cnt { 0b1 }, "a"));
static_assert(many(cntp())("BBa") == succeed(cnt { 0b11 }, "a"));
static_assert(many(cntp())("BBB") == succeed(cnt { 0b111 }, "")); // NOLINT
static_assert(many(cntp(), cnt_init {})("") == succeed(cnt_init {}, ""));
static_assert(many(cntp(), cnt_init {})("a") == succeed(cnt_init {}, "a"));
static_assert(many(cntp(), cnt_init {})("B") == succeed(cnt_init { 1 }, ""));
