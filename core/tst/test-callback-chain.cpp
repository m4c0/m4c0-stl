#include "m4c0/callback_chain.hpp"
#include "m4c0/test.hpp"

template<bool Success, int id>
class cb {
  bool m_called { false };

public:
  explicit cb(m4c0::callback_chain<int(int)> & chain) {
    chain.add(this, &cb::call);
  }

  std::optional<int> call(int a) {
    m_called = true;
    if constexpr (Success) {
      constexpr const auto decimal = 10;
      return { a + id * decimal };
    }
    return {};
  }

  [[nodiscard]] constexpr auto called() const noexcept {
    return m_called;
  }
};

go_bandit([] { // NOLINT
  describe("callback_chain", [] {
    it("accepts the first callback", [] {
      m4c0::callback_chain<int(int)> chain;
      cb<true, 1> a { chain };
      AssertThat(chain(1), Is().EqualTo(11));
    });

    it("ignores empty results", [] {
      m4c0::callback_chain<int(int)> chain;
      cb<false, 1> a { chain };
      cb<true, 2> b { chain };
      AssertThat(chain(1), Is().EqualTo(21));
      AssertThat(a.called(), Is().True());
    });

    it("ignores callbacks after a success", [] {
      m4c0::callback_chain<int(int)> chain;
      cb<true, 1> a { chain };
      cb<true, 2> b { chain };
      AssertThat(chain(1), Is().EqualTo(11));
      AssertThat(b.called(), Is().False());
    });

    it("ignores callbacks after a success, even if result would be empty", [] {
      m4c0::callback_chain<int(int)> chain;
      cb<true, 1> a { chain };
      cb<false, 2> b { chain };
      AssertThat(chain(1), Is().EqualTo(11));
      AssertThat(b.called(), Is().False());
    });

    it("returns default values if all results are empty", [] {
      m4c0::callback_chain<int(int)> chain;
      cb<false, 1> a { chain };
      cb<false, 2> b { chain };
      AssertThat(chain(1), Is().EqualTo(0));
      AssertThat(a.called(), Is().True());
      AssertThat(b.called(), Is().True());
    });
  });
});
