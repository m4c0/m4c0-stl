#include "m4c0/di.hpp"
#include "m4c0/di/scope.hpp"
#include "m4c0/test.hpp"

using namespace m4c0::di;

class srv1 {};
class srv2 {
  srv1 * m_s1;

public:
  explicit srv2(srv1 * s1) : m_s1(s1) {
  }

  [[nodiscard]] constexpr srv1 * s1() const noexcept {
    return m_s1;
  }
};

go_bandit([] { // NOLINT
  describe("scope", [] {
    it("can get a unique instance after bind", [] {
      scope s;
      s.bind<srv1>();
      s.bind<srv2, srv1>();

      srv2 * s2 = s.get<srv2>();
      AssertThat(s2, Is().Not().Null());
      AssertThat(s2->s1(), Is().EqualTo(s.get<srv1>()));
      AssertThat(s2, Is().EqualTo(s.get<srv2>()));
    });
    it("can bind with delegation", [] {
      scope a;
      a.bind<srv1>();

      scope b { &a };
      b.bind<srv2, srv1>();

      srv2 * s2 = b.get<srv2>();
      AssertThat(s2, Is().Not().Null());
      AssertThat(s2->s1(), Is().EqualTo(a.get<srv1>()));
    });
    it("gives a different instance after reset", [] {
      scope s;
      s.bind<srv1>();

      srv1 * before = s.get<srv1>();
      s.reset();

      srv1 * after = s.get<srv1>();
      AssertThat(after, Is().Not().Null());
      AssertThat(after, Is().Not().EqualTo(before));
    });
    it("can bind with delegation after a reset", [] {
      scope a;
      a.bind<srv1>();

      scope b { &a };
      b.bind<srv2, srv1>();

      srv2 * before = b.get<srv2>();
      b.reset();

      srv2 * after = b.get<srv2>();
      AssertThat(after, Is().Not().Null());
      AssertThat(after, Is().Not().EqualTo(before));
      AssertThat(after->s1(), Is().EqualTo(a.get<srv1>()));
    });
  });
});
