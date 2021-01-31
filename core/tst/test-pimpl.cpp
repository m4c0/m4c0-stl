#include "m4c0/pimpl.hpp"
#include "m4c0/test.hpp"

using m4c0::pimpl;

go_bandit([] { // NOLINT
  describe("pimpl", [] {
    it("does not create a instance when default constructed", [] {
      class dummy;
      pimpl<dummy> p {};
      AssertThat(p.get(), Is().Null());
    });
    it("creates a instance on-demand", [] {
      class dummy {};
      pimpl<dummy> p {};
      p.make_new();
      AssertThat(p.get(), Is().Not().Null());
    });
    it("clears when reset", [] {
      class dummy {};
      pimpl<dummy> p {};
      p.make_new();
      p.reset();
      AssertThat(p.get(), Is().Null());
    });
    it("is accesible with arrow/star operator", [] {
      struct dummy {
        int d = 3;
      };
      pimpl<dummy> p {};
      p.make_new();
      AssertThat(p->d, Is().EqualTo(3));
      AssertThat((*p).d, Is().EqualTo(3));
    });
    it("casts to false when there is no value", [] {
      class dummy;
      pimpl<dummy> p {};
      AssertThat((bool)p, Is().False());
    });
    it("casts to true when there is a value", [] {
      class dummy {};
      pimpl<dummy> p {};
      p.make_new();
      AssertThat((bool)p, Is().True());
    });
    it("destroys the contained instance", [] {
      static int count = 0;
      struct dummy { // NOLINT
        ~dummy() {
          count++;
        }
      };
      int old_count = count;
      {
        pimpl<dummy> p {};
        p.make_new();
      }
      AssertThat(count, Is().EqualTo(old_count + 1));
    });
    it("moves its instance", [] {
      class dummy {};
      pimpl<dummy> a {};
      a.make_new();
      dummy * d = a.get();

      pimpl<dummy> b = std::move(a);
      AssertThat(b.get(), Is().EqualTo(d));
    });
  });
});
