#include "m4c0/parser/numeric.hpp"

using namespace m4c0::parser;

static_assert(!match_digit()(""));
static_assert(!match_digit()("a1"));
static_assert(match_digit()("1234") == success { 1, "234" });
