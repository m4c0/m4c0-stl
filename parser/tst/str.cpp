#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

static_assert(!match('A')(""));
static_assert(!match('A')("_"));
static_assert(match('A')("A") == success { 'A', "" });
static_assert(match('A')("AB") == success { 'A', "B" });

static_assert(!match("ABC")(""));
static_assert(!match("ABC")("AB"));
static_assert(!match("ABC")("AABC"));
static_assert(match("ABC")("ABC") == success<input_t> { "ABC", "" });
static_assert(match("ABC")("ABCD") == success<input_t> { "ABC", "D" });

static_assert(!match_any_of("ABC")(""));
static_assert(!match_any_of("ABC")("D"));
static_assert(match_any_of("ABC")("A") == success { 'A', "" });
static_assert(match_any_of("ABC")("B") == success { 'B', "" });
static_assert(match_any_of("ABC")("C") == success { 'C', "" });
static_assert(match_any_of("ABC")("ABC") == success { 'A', "BC" });
static_assert(match_any_of("ABC")("BC") == success { 'B', "C" });

static_assert(!match_range('a', 'z')(""));
static_assert(!match_range('a', 'z')("0"));
static_assert(match_range('a', 'z')("a") == success { 'a', "" });
static_assert(match_range('a', 'z')("d") == success { 'd', "" });
static_assert(match_range('a', 'z')("z") == success { 'z', "" });
static_assert(match_range('a', 'z')("zaza") == success { 'z', "aza" });

static_assert(!match_none_of("ABC")(""));
static_assert(!match_none_of("ABC")("A"));
static_assert(!match_none_of("ABC")("B"));
static_assert(!match_none_of("ABC")("C"));
static_assert(match_none_of("ABC")("D") == success { 'D', "" });
static_assert(match_none_of("ABC")("EF") == success { 'E', "F" });

static_assert(!tokenise(match('X'))(""));
static_assert(!tokenise(match('X'))("A"));
static_assert(tokenise(match('X'))("X") == success<input_t> { "X", "" });
static_assert(tokenise(match('X'))("XX") == success<input_t> { "X", "X" });
static_assert(tokenise(match('X'))("Xx") == success<input_t> { "X", "x" });
