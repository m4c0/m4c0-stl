#include "m4c0/parser/numeric.hpp"

using namespace m4c0::parser;

static_assert(!match_digit()(""));
static_assert(!match_digit()("a1"));
static_assert(match_digit()("1234") == success { 1, "234" });

static_assert(!match_u32()(""));
static_assert(!match_u32()("a1"));
static_assert(match_u32()("203") == success { 203U, "" }); // NOLINT
static_assert(match_u32()("0") == success { 0U, "" });
static_assert(match_u32()("02") == success { 2U, "" });
static_assert(match_u32()("12a") == success { 12U, "a" }); // NOLINT
