#include "m4c0/function.hpp"
#include "m4c0/test.hpp"

go_bandit([] { // NOLINT
  describe("function", [] {
    it("has a default constructor", [] {
      m4c0::function<int()> fn {};
      AssertThrows(std::runtime_error, fn());
    });
    it("stores and call a captureless lambda", [] {
      m4c0::function<int()> fn([]() -> int {
        return 1;
      });
      AssertThat(fn(), Is().EqualTo(1));
    });

    it("stores and call a stateful lambda", [] {
      int i = 2;
      m4c0::function<int()> fn([&i]() -> int {
        return i;
      });
      AssertThat(fn(), Is().EqualTo(2));
    });

    it("works after moving", [] {
      int i = 3;
      m4c0::function<int()> fn([&i]() -> int {
        return i;
      });
      auto fn2 = std::move(fn);

      AssertThat(fn2(), Is().EqualTo(3));
    });
  });
});
