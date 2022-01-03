#include "m4c0/parser/numeric.hpp"

using namespace m4c0::parser;

template<typename Tp>
static constexpr auto succeed(Tp res, input_t rem) {
  return result { success { res }, rem };
}

static_assert(!match_digit()(""));
static_assert(!match_digit()("a1"));
static_assert(match_digit()("1234") == succeed(1, "234"));

static_assert(!match_u32()(""));
static_assert(!match_u32()("a1"));
static_assert(match_u32()("203") == succeed(203U, "")); // NOLINT
static_assert(match_u32()("0") == succeed(0U, ""));
static_assert(match_u32()("02") == succeed(2U, ""));
static_assert(match_u32()("12a") == succeed(12U, "a")); // NOLINT

static_assert(!match_s32()(""));
static_assert(!match_s32()("a1"));
static_assert(match_s32()("203") == succeed(203, "")); // NOLINT
static_assert(match_s32()("0") == succeed(0, ""));
static_assert(match_s32()("02") == succeed(2, ""));
static_assert(match_s32()("12a") == succeed(12, "a"));   // NOLINT
static_assert(match_s32()("-203") == succeed(-203, "")); // NOLINT
static_assert(match_s32()("-0") == succeed(0, ""));
static_assert(match_s32()("-02") == succeed(-2, ""));
static_assert(match_s32()("-12a") == succeed(-12, "a")); // NOLINT
