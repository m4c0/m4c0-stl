#include "m4c0/parser/result.hpp"
#include "m4c0/test.hpp"

using namespace m4c0::parser;

go_bandit([] { // NOLINT
  describe("m4c0::parser", [] {
    it("can create a valid polish notation parser", [] {
      constexpr const auto p = [](auto /*in*/) -> int {
        return 0;
      };
      AssertThat(p("+ 3 4"), Is().EqualTo(7));
      AssertThat(p("+ - 4 1 9"), Is().EqualTo(12));
    });
  });
});
