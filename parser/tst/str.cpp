#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;
using str = std::string_view;

static_assert(!match('A')(""));
static_assert(!match('A')("_"));
static_assert(match('A')("A") == success { 'A', "" });
static_assert(match('A')("AB") == success { 'A', "B" });

static_assert(!match("ABC")(""));
static_assert(!match("ABC")("AB"));
static_assert(!match("ABC")("AABC"));
static_assert(match("ABC")("ABC") == success<str> { "ABC", "" });
static_assert(match("ABC")("ABCD") == success<str> { "ABC", "D" });

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
