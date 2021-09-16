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

static_assert([] {
  constexpr auto str = sv("OKAY DOKAY");
  constexpr auto dokay = str.substr(5);
  constexpr auto okay = str.up_to(str.substr(4));

  static_assert(okay == sv("OKAY"));

  static_assert(dokay.up_to(str).empty());

  static_assert(okay.up_to(str).empty());
  static_assert(str.up_to(okay).empty());

  static_assert(okay.up_to(dokay).empty());

  static_assert(str.up_to(dokay).up_to(dokay) == sv("OKAY "));
  return true;
}());
