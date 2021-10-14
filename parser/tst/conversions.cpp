#include "m4c0/parser/combiners.hpp"
#include "m4c0/parser/conversions.hpp"
#include "m4c0/parser/str.hpp"

using namespace m4c0::parser;

static constexpr const auto p = match('@') & to<int>();
static_assert(!p(""));
static_assert(!p("!"));
static_assert(p("@") == result { success<int> { '@' }, "" });
static_assert(p("@@") == result { success<int> { '@' }, "@" });
static_assert(p("@b") == result { success<int> { '@' }, "b" });
