#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/numeric.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

struct oper {
  int (*fn)(int, int);
};
struct oper_and_value {
  int (*fn)(int, int);
  int value;
};
static constexpr oper_and_value operator+(oper o, int n) {
  return { o.fn, n };
}
static constexpr oper_and_value operator+(oper_and_value o, int n) {
  return { o.fn, o.fn(o.value, n) };
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
static constexpr auto digit = match_digit();

static constexpr auto expr = many(space_chr) & oper_sign + space + digit + space + digit;

static_assert(*expr("+ 3 4") == 3 + 4);
static_assert(*expr("- 4 1") == 4 - 1);

static_assert(*expr("  +  1  2  ") == 1 + 2);
