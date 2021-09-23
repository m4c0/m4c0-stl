#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/constants.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

static_assert(!fail<char>("")(""));
static_assert(fail<char>("msg")("rem") == result { failure<char> { "msg" }, "rem" });
static_assert((match('X') | fail<char>("msg"))("rem") == result { failure<char> { "msg" }, "rem" });
static_assert((match('r') & fail<char>("msg"))("rem") == result { failure<char> { "msg" }, "em" });
