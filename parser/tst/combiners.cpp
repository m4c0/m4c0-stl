#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/result.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

static constexpr auto to_int(char c) {
  return c - '0';
}
static_assert(to_int('3') == 3); // When a test needs test, are we doing the right thing?

static_assert(!fmap(to_int, match_range('0', '9'))("A3"));
static_assert(fmap(to_int, match_range('0', '9'))("37") == success { 3, "7" });
