#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/result.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

static constexpr auto fn(char c) {
  return c - 'A';
}
static_assert(fn('C') == 2); // When a test needs test, are we doing the right thing?

static_assert(!fmap(fn, match_range('A', 'Z'))("cZ"));
static_assert(fmap(fn, match_range('A', 'Z'))("Cz") == success { 2, "z" });

static_assert((match('a') | failure<char>("ok"))("aha") == success { 'a', "ha" });
static_assert((match('a') | failure<char>("ok"))("nope") == failure<char>("ok"));

static_assert((match('a') | "nok")("aha") == success { 'a', "ha" });
static_assert((match('a') | "nok")("nope") == failure<char>("nok"));
