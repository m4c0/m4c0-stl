#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/numeric.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

struct value {
  int d = 0;
};
static constexpr bool operator==(const value o, const int n) noexcept {
  return o.d == n;
}
static constexpr auto to_value(int d) noexcept {
  return value { d };
}

struct oper {
  int (*fn)(int, int) noexcept;
};
struct oper_and_value : public oper, public value {};
static constexpr oper_and_value operator+(const oper o, const value n) noexcept {
  return { o.fn, n.d };
}
static constexpr oper_and_value operator+(const oper_and_value o, const value n) noexcept {
  return { o.fn, o.fn(o.d, n.d) };
}
static constexpr auto slice_value(const oper_and_value v) noexcept {
  return value { v.d };
}

static constexpr auto plus(int a, int b) noexcept {
  return a + b;
};
static constexpr auto minus(int a, int b) noexcept {
  return a - b;
};

static constexpr auto plus_sign = match('+') & oper { plus };
static constexpr auto minus_sign = match('-') & oper { minus };
static constexpr auto oper_sign = plus_sign | minus_sign;

static constexpr auto space_chr = skip(match_any_of(" \r\n\t"));
static constexpr auto space = at_least_one(space_chr);
static constexpr auto number = match_u32() & to_value;

static constexpr auto rec() noexcept -> result<value> (*)(input_t) noexcept {
  return [](input_t in) noexcept -> result<value> {
    const auto op = oper_sign + space + rec() + space + rec();
    const auto p = (op & slice_value) | number;
    return p(in);
  };
}

struct result_visitor {
  constexpr value operator()(value res) const noexcept {
    return res;
  }
  constexpr value operator()(input_t /*err*/) const noexcept {
    return { -1 };
  }
};
static constexpr auto expr = many(space_chr) & rec();

static constexpr auto parse(input_t in) {
  return expr(in) % result_visitor {};
}

static_assert(parse("+ 3 4") == 3 + 4);
static_assert(parse("- 4 1") == 3);

static_assert(parse("  +  1  2  ") == 3);

static_assert(parse("- 22 020") == 2);

static_assert(parse("+ - 4 1 + 3 1") == 3 + 4);
