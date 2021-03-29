#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/middleware.hpp"

#undef Nil
#include "m4c0/test.hpp"

static auto dummy() {
  return 3;
}

go_bandit([] { // NOLINT
  describe("objc-bridge pre-reqs", [] {
    it("can create an autorelease pool", [] {
      m4c0::objc::autorelease_pool pool;
    });
  });

  describe("objc-bridge for classes", [] {
    it("creates instances of a base class", [] {
      m4c0::objc::middleware midware;
      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for_class("NSObject");
      AssertThat(obj, Is().Not().Null());
    });
    it("creates instances of a base class a second time", [] {
      // This validates if next tests will have a chance of succeeding
      m4c0::objc::middleware midware;
      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for_class("NSObject");
      AssertThat(obj, Is().Not().Null());
    });
    it("can invoke methods from the base class", [] {
      m4c0::objc::middleware midware;
      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for_class("NSObject");
      void * str = m4c0::objc::objc_msg_send<void *>(obj, "className");
      const char * cstr = m4c0::objc::objc_msg_send<const char *>(str, "UTF8String");
      AssertThat(cstr, Is().EqualTo("M4C0_$$_NSObject"));
    });
    it("override methods from base class", [] {
      m4c0::objc::middleware midware;
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      auto imp = reinterpret_cast<m4c0::objc::middleware::imp_t>(&dummy);
      midware.add_imp("length", imp);

      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for_class("NSString");
      int res = m4c0::objc::objc_msg_send<int>(obj, "length");
      AssertThat(res, Is().EqualTo(dummy()));
    });
  });

  describe("objc-bridge for protocols", [] {
    it("creates instances of a protocol", [] {
      m4c0::objc::middleware midware;
      m4c0::objc::autorelease_pool pool;

      void * obj = midware.create_for_protocol("NSUserActivityDelegate");
      AssertThat(obj, Is().Not().Null());
    });
  });
});
