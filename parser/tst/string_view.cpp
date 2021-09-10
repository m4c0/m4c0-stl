#include "m4c0/parser/string_view.hpp"

using sv = m4c0::parser::string_view;

static_assert(sv { "OK" } == sv { "OK" });
static_assert(sv { "OK" } != sv { "OKay" });
static_assert(sv("OK").at(1) == 'K');
static_assert(sv("OK").contains('K'));
static_assert(!sv("OK").contains('k'));
static_assert(sv("").empty());
static_assert(!sv("A").empty());
static_assert(sv("OKAY").starts_with("OK"));
static_assert(!sv("OKAY").starts_with("AY"));
static_assert(!sv("OK").starts_with("OKAY"));
static_assert(sv("OKAY").substr(2) == sv { "AY" });
