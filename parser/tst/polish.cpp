#include "m4c0/parser/result.hpp"
#include "m4c0/test.hpp"

#include <optional>

using namespace m4c0::parser;

using str = std::string_view;

constexpr auto match(char c) noexcept {
  return [c](str in) -> result<char> {
    if (in.empty()) return failure<char>("EOF");
    if (in.at(0) != c) return failure<char>("Mismatched char");
    return success { c };
  };
}

static_assert(!match('A')(""));
static_assert(!match('A')("_"));
static_assert(match('A')("A") == success { 'A' });

go_bandit([] { // NOLINT
  describe("m4c0::parser", [] {
    it("can create a valid polish notation parser", [] {
      constexpr const auto p = [](auto /*in*/) -> int {
        return 0;
      };
      AssertThat(p("+ 3 4"), Is().EqualTo(7));
      AssertThat(p("+ - 4 1 9"), Is().EqualTo(10));
    });
  });
});
