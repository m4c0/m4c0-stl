#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/result.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

static constexpr auto fnp() {
  return match_range('A', 'Z') & [](char c) {
    return c - 'A';
  };
}
static_assert(!fnp()(""));
static_assert(!fnp()("cZ"));
static_assert(fnp()("Cz") == success { 2, "z" });

static_assert(!(match('a') & fnp())(""));
static_assert(!(match('a') & fnp())("a"));
static_assert(!(match('a') & fnp())("bA"));
static_assert((match('a') & fnp())("aAb") == success { 0, "b" });

static_assert((match('a') & 4)("aha") == success { 4, "ha" });
static_assert(!(match('a') & 4)("nope"));

static_assert(!(match('a') + fnp())(""));
static_assert(!(match('a') + fnp())("a"));
static_assert(!(match('a') + fnp())("bA"));
static_assert((match('b') + fnp())("bCa") == success { 'b' + 2, "a" });

static_assert(!(3 + fnp())(""));
static_assert((3 + fnp())("C") == success { 3 + 2, "" });
static_assert((3 + fnp())("CD") == success { 3 + 2, "D" });

static_assert((match('a') | failure<>("ok"))("aha") == success { 'a', "ha" });
static_assert((match('a') | failure<>("ok"))("nope") == failure<>("ok"));

static_assert((match('a') | 'b')("aha") == success { 'a', "ha" });
static_assert((match('a') | 'b')("nope") == success { 'b', "nope" });

static_assert((match('a') | "nok")("aha") == success { 'a', "ha" });
static_assert((match('a') | "nok")("nope") == failure<char>("nok"));

static_assert(!(match('a') | match('c'))(""));
static_assert(!(match('a') | match('c'))("bc"));
static_assert((match('a') | match('c'))("ac") == success { 'a', "c" });
static_assert((match('a') | match('c'))("c") == success { 'c', "" });

static_assert(!skip(match('a'))(""));
static_assert(!skip(match('a'))("b"));
static_assert(skip(match('a'))("ab") == success { nil {}, "b" });

static_assert((match('a') + skip(match('b')))("ab") == success { 'a', "" });

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

static_assert(!at_least_one(cntp())(""));
static_assert(!at_least_one(cntp())("a"));
static_assert(at_least_one(cntp())("B") == success { cnt { 0b1 }, "" });
static_assert(at_least_one(cntp())("Ba") == success { cnt { 0b1 }, "a" });
static_assert(at_least_one(cntp())("BBa") == success { cnt { 0b11 }, "a" });
static_assert(at_least_one(cntp())("BBB") == success { cnt { 0b111 }, "" });   // NOLINT
static_assert(at_least_one(cntp())("BBBa") == success { cnt { 0b111 }, "a" }); // NOLINT
static_assert(!at_least_one(cntp(), cnt_init {})(""));
static_assert(at_least_one(cntp(), cnt_init {})("B") == success { cnt_init { 1 }, "" }); // NOLINT

static_assert(many(cntp())("") == success { cnt {}, "" });
static_assert(many(cntp())("a") == success { cnt {}, "a" });
static_assert(many(cntp())("B") == success { cnt { 0b1 }, "" });
static_assert(many(cntp())("Ba") == success { cnt { 0b1 }, "a" });
static_assert(many(cntp())("BBa") == success { cnt { 0b11 }, "a" });
static_assert(many(cntp())("BBB") == success { cnt { 0b111 }, "" }); // NOLINT
static_assert(many(cntp(), cnt_init {})("") == success { cnt_init {}, "" });
static_assert(many(cntp(), cnt_init {})("a") == success { cnt_init {}, "a" });
static_assert(many(cntp(), cnt_init {})("B") == success { cnt_init { 1 }, "" });
