#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/numeric.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

struct value {
  int d = 0;
};
static constexpr value operator+(const value a, const value b) {
  constexpr const auto radix = 10;
  return value { a.d * radix + b.d };
}
static constexpr bool operator==(const value o, const int n) {
  return o.d == n;
}
static constexpr auto to_value(int d) {
  return value { d };
}

struct oper {
  int (*fn)(int, int);
};
struct oper_and_value : public oper, public value {};
static constexpr oper_and_value operator+(const oper o, const value n) {
  return { o.fn, n.d };
}
static constexpr oper_and_value operator+(const oper_and_value o, const value n) {
  return { o.fn, o.fn(o.d, n.d) };
}
static constexpr auto slice_value(const oper_and_value v) {
  return value { v.d };
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
static constexpr auto number = at_least_one(match_digit() & to_value);

static constexpr auto rec() -> result<value> (*)(std::string_view) {
  return [](std::string_view in) -> result<value> {
    const auto op = oper_sign + space + rec() + space + rec();
    const auto p = (op & slice_value) | number;
    return p(in);
  };
}
static constexpr auto expr = many(space_chr) & rec();

static_assert(*expr("+ 3 4") == 3 + 4);
static_assert(*expr("- 4 1") == 3);

static_assert(*expr("  +  1  2  ") == 3);

static_assert(*expr("- 22 020") == 2);

static_assert(*expr("+ - 4 1 + 3 1") == 3 + 4);
