#include "m4c0/di.hpp"
#include "m4c0/di/type_id.hpp"
#include "m4c0/test.hpp"

class srv1 {};
class srv2 {};
class srv3 { // NOLINT
  srv1 * m_1;
  srv2 * m_2;

public:
  static int & deleted_count() {
    static int count = 0;
    return count;
  }

  srv3(srv1 * p1, srv2 * p2) : m_1(p1), m_2(p2) {
  }
  ~srv3() {
    deleted_count()++;
  }

  [[nodiscard]] srv1 * get_1() const noexcept {
    return m_1;
  }
  [[nodiscard]] srv2 * get_2() const noexcept {
    return m_2;
  }
};

class gadget : public srv3 {
public:
  using srv3::srv3;
};
std::unique_ptr<gadget> factory(srv1 * p1, srv3 * p3) {
  return std::make_unique<gadget>(p1, p3->get_2());
}

go_bandit([] { // NOLINT
  using namespace m4c0::di;

  config cfg;
  before_each([&] {
    cfg = {};
    cfg.bind<srv3, srv1, srv2>();
    cfg.bind<srv2>();
    cfg.bind<srv1>();
  });

  describe("injector", [&] {
    injector inj;

    before_each([&] {
      inj = cfg.build_injector();
    });

    it("can inject a service with dependencies", [&] {
      AssertThat(inj.get<srv3>(), Is().Not().Null());
    });
    it("doesn't create duplicate instances", [&] {
      auto * s3 = inj.get<srv3>();
      AssertThat(inj.get<srv3>(), Is().EqualTo(s3));
    });
    it("contains all dependencies", [&] {
      auto * s3 = inj.get<srv3>();
      AssertThat(s3->get_1(), Is().Not().Null());
      AssertThat(s3->get_2(), Is().Not().Null());
    });

    describe("when injecting with custom factories", [&] {
      std::unique_ptr<gadget> g;

      before_each([&] {
        g = inj.inject(factory);
      });

      it("can inject", [&] {
        AssertThat(g, Is().Not().Null());
      });
      it("inject the dependencies", [&] {
        AssertThat(g->get_1(), Is().Not().Null());
        AssertThat(g->get_2(), Is().Not().Null());
      });
    });
  });

  describe("multiple injectors", [&] {
    injector inj_a;
    injector inj_b;

    before_each([&] {
      inj_a = cfg.build_injector();
      inj_b = cfg.build_injector();
    });

    it("creates independent instances", [&] {
      auto * s1_a = inj_a.get<srv1>();
      auto * s1_b = inj_b.get<srv1>();
      AssertThat(s1_a, Is().Not().EqualTo(s1_b));
    });
  });

  describe("injector lifecycle", [&] {
    auto build_s3 = [&]() -> srv3 * {
      return cfg.build_injector().get<srv3>();
    };
    it("cleans up instances when destroyed", [&] {
      int count = srv3::deleted_count();
      build_s3();

      AssertThat(srv3::deleted_count(), Is().EqualTo(count + 1));
    });
    it("destroy instances in the proper order", [] {
      static std::string buf {};

      struct a { // NOLINT
        ~a() {
          buf += "a";
        }
      };
      struct b { // NOLINT
        explicit b(a * /**/) {
        }
        ~b() {
          buf += "b";
        }
      };
      struct c { // NOLINT
        explicit c(b * /**/) {
        }
        ~c() {
          buf += "c";
        }
      };

      // Forces an ID order
      type_id::of<b>();
      type_id::of<a>();
      type_id::of<c>();

      config cfg {};
      cfg.bind<a>();
      cfg.bind<b, a>();
      cfg.bind<c, b>();
      { auto i = cfg.build_injector(); }

      AssertThat(buf, Is().EqualTo("cba"));
    });
  });

  describe("injector delegation", [] {
    it("can delegate injection", [] {
      config ca;
      ca.bind<srv1>();
      ca.bind<srv2>();
      injector a = ca.build_injector();

      config cb;
      cb.bind<srv3, srv1, srv2>();
      injector b = cb.build_injector(&a);

      srv3 * s3 = b.get<srv3>();
      AssertThat(s3, Is().Not().Null());
      AssertThat(s3->get_1(), Is().EqualTo(a.get<srv1>()));
      AssertThat(s3->get_2(), Is().EqualTo(a.get<srv2>()));
    });
  });

  describe("config", [&] {
    it("can be reused", [&] {
      injector a = cfg.build_injector();
      injector b = cfg.build_injector();

      AssertThat(a.get<srv1>(), Is().Not().Null());
      AssertThat(b.get<srv1>(), Is().Not().Null());
      AssertThat(a.get<srv1>(), Is().Not().EqualTo(b.get<srv1>()));
    });

    it("align properly", [&] {
      config c {};
      c.bind<srv1>();
      c.bind<srv2>();
      c.bind<srv3, srv1, srv2>();

      injector i = c.build_injector();

      void * ptr = i.get<srv3>();
      size_t size_we_dont_care = 100000000; // NOLINT
      ptr = std::align(alignof(srv3), sizeof(srv3), ptr, size_we_dont_care);

      AssertThat(i.get<srv3>(), Is().Not().Null().And().EqualTo(ptr));
    });
  });
});
