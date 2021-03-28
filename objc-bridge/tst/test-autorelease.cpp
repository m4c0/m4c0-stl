#include "m4c0/objc/autorelease_pool.hpp"

#undef Nil
#include "m4c0/test.hpp"

static bool flipped = false; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
static void flip(id /*self*/, SEL /*sel*/) {
  flipped = true;
}

go_bandit([] { // NOLINT
  describe("objc-bridge", [] {
    it("can create an autorelease pool", [] {
      Class cls = objc_allocateClassPair(objc_getClass("NSObject"), "Test", 0);
      SEL sel = sel_getUid("dealloc");
      class_addMethod(cls, sel, m4c0::objc::to_imp(&flip), "v@:");

      {
        m4c0::objc::autorelease_pool pool;
        m4c0::objc::objc_msg_send<id>(m4c0::objc::objc_msg_send<id>(cls, "new"), "autorelease");
      }
      AssertThat(flipped, Is().True());
    });
  });
});
