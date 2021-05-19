#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"

#undef Nil
#include "m4c0/test.hpp"

#include <CoreFoundation/CoreFoundation.h>

go_bandit([] { // NOLINT
  describe("class_builder", [] {
    it("can survive ISA swizzing", [] {
      m4c0::objc::autorelease_pool pool;

      const char * cls_name_a = m4c0::objc::class_builder("NSObject").add_ptr_ivar("test").build();
      Class cls_a = objc_getClass(cls_name_a);
      id obj = m4c0::objc::objc_msg_send<id>(cls_a, "new");
      m4c0::objc::object_set_ivar(obj, "test", &pool);

      const char * cls_name_b = m4c0::objc::class_builder(cls_name_a).build();
      Class cls_b = objc_getClass(cls_name_b);

      object_setClass(obj, cls_b);

      void * ptr = m4c0::objc::object_get_ivar<void *>(obj, "test");
      AssertThat(ptr, Is().EqualTo(&pool));
    });
    it("can survive object observing", [] {
      m4c0::objc::autorelease_pool pool;

      const char * cls_name = m4c0::objc::class_builder("NSObject").add_ptr_ivar("test").build();
      Class cls = objc_getClass(cls_name);
      id obj = m4c0::objc::objc_msg_send<id>(cls, "new");
      id obs = m4c0::objc::objc_msg_send<id>(cls, "new");
      m4c0::objc::object_set_ivar(obj, "test", &pool);

      CFStringRef attr = CFSTR("class"); // NOLINT
      m4c0::objc::objc_msg_send<void>(obj, "addObserver:forKeyPath:options:context:", obs, attr, 0, nullptr);

      AssertThat(object_getClass(obj), Is().Not().EqualTo(cls));

      void * ptr = m4c0::objc::object_get_ivar<void *>(obj, "test");
      AssertThat(ptr, Is().EqualTo(&pool));
    });
  });
});
