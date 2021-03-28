#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/middleware.hpp"

#undef Nil
#include "m4c0/test.hpp"

static auto dummy() {
  return 3;
}

go_bandit([] { // NOLINT
  describe("objc-bridge", [] {
    it("can create an autorelease pool", [] {
      m4c0::objc::autorelease_pool pool;
    });
    it("creates instances of a base class", [] {
      m4c0::objc::middleware midware;
      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for("NSObject");
      AssertThat(obj, Is().Not().Null());
    });
    it("creates instances of a base class a second time", [] {
      // This validates if next tests will have a chance of succeeding
      m4c0::objc::middleware midware;
      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for("NSObject");
      AssertThat(obj, Is().Not().Null());
    });
    it("can invoke methods from the base class", [] {
      m4c0::objc::middleware midware;
      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for("NSObject");
      void * str = m4c0::objc::objc_msg_send<void *>(obj, "className");
      const char * cstr = m4c0::objc::objc_msg_send<const char *>(str, "UTF8String");
      AssertThat(cstr, Is().EqualTo("M4C0_$$_NSObject"));
    });
    it("override methods", [] {
      m4c0::objc::middleware midware;
      midware.add_forward("length", &dummy);

      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for("NSString");
      int res = m4c0::objc::objc_msg_send<int>(obj, "length");
      AssertThat(res, Is().EqualTo(dummy()));
    });
  });
});
