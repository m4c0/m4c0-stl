#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/numeric.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

struct digit {
  int d = 0;
};
static constexpr digit operator+(const digit a, const digit b) {
  constexpr const auto radix = 10;
  return digit { a.d * radix + b.d };
}
static constexpr auto to_digit(int d) {
  return digit { d };
}

struct oper {
  int (*fn)(int, int);
};
struct oper_and_value {
  int (*fn)(int, int);
  int value;
};
static constexpr oper_and_value operator+(oper o, digit n) {
  return { o.fn, n.d };
}
static constexpr oper_and_value operator+(oper_and_value o, digit n) {
  return { o.fn, o.fn(o.value, n.d) };
}
static constexpr bool operator==(oper_and_value o, int n) {
  return o.value == n;
}

static constexpr auto plus(int a, int b) {
  return a + b;
};
static constexpr auto minus(int a, int b) {
  return a - b;
};

static constexpr auto plus_sign = match('+') & oper { plus };
static constexpr auto minus_sign = match('-') & oper { minus };
static constexpr auto oper_sign = plus_sign | minus_sign;

static constexpr auto space_chr = skip(match_any_of(" \r\n\t"));
static constexpr auto space = at_least_one(space_chr);
static constexpr auto number = at_least_one(match_digit() & to_digit);

static constexpr auto expr = many(space_chr) & oper_sign + space + number + space + number;

static_assert(*expr("+ 3 4") == 3 + 4);
static_assert(*expr("- 4 1") == 3);

static_assert(*expr("  +  1  2  ") == 3);

static_assert(*expr("- 22 020") == 2);
