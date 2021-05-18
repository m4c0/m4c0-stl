#include "m4c0/objc/autorelease_pool.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/class_builder.hpp"

#undef Nil
#include "m4c0/test.hpp"

class my_cls {
  int b;

public:
  explicit my_cls(int b) : b(b) {
  }
  [[nodiscard]] int add(int a) const {
    return a + b;
  }
};
class my_virt_cls {
  int b;

public:
  explicit my_virt_cls(int b) : b(b) {
  }
  [[nodiscard]] virtual int add(int a) const {
    return a + b;
  }
};
static int add(void * /*self*/, void * /*sel*/, int a, int b) {
  return a + b;
}
static int add_from_obj(void * self, void * /*sel*/) {
  int a = m4c0::objc::object_get_ivar<int>(self, "a");
  int b = m4c0::objc::object_get_ivar<int>(self, "b");
  return a + b;
}

static void * create_object(const char * cls_name) {
  Class cls = objc_getClass(cls_name);

  auto * obj = m4c0::objc::objc_msg_send<void *>(cls, "alloc");
  AssertThat(obj, Is().Not().Null());

  obj = m4c0::objc::objc_msg_send<void *>(obj, "init");
  AssertThat(obj, Is().Not().Null());

  return obj;
}

go_bandit([] { // NOLINT
  describe("class_builder", [] {
    it("creates callable classes", [] {
      m4c0::objc::autorelease_pool pool;

      const char * cls_name =
          m4c0::objc::class_builder("NSObject").add_method("sum:with:", m4c0::objc::to_imp(add), "i@:ii").build();
      auto * obj = create_object(cls_name);

      static constexpr const auto a = 1238;
      static constexpr const auto b = 8568;

      int res = m4c0::objc::objc_msg_send<int>(obj, "sum:with:", a, b);
      AssertThat(res, Is().EqualTo(a + b));
    });
    it("can set ivars", [] {
      m4c0::objc::autorelease_pool pool;

      const char * cls_name = m4c0::objc::class_builder("NSObject")
                                  .add_typed_ivar<int>("a", "i")
                                  .add_typed_ivar<int>("b", "i")
                                  .add_method("sum", m4c0::objc::to_imp(add_from_obj), "i@:")
                                  .build();
      auto * obj = create_object(cls_name);

      static constexpr const auto a = 5742;
      static constexpr const auto b = 1569;
      m4c0::objc::object_set_ivar(obj, "a", int { a });
      m4c0::objc::object_set_ivar(obj, "b", int { b });

      auto res = m4c0::objc::objc_msg_send<int>(obj, "sum");
      AssertThat(res, Is().EqualTo(a + b));
    });
  });

  describe("delegated_class_builder", [] {
    it("creates delegatable classes", [] {
      static constexpr const auto a = 3497;
      static constexpr const auto b = 3657;

      m4c0::objc::autorelease_pool pool;

      const char * cls_name =
          m4c0::objc::delegated_class_builder<my_cls>("NSObject").add_method<&my_cls::add>("sumWith:", "i@:i").build();
      auto * obj = create_object(cls_name);

      my_cls my_obj { b };
      m4c0::objc::delegated_class_builder<my_cls>::set_ivar(obj, &my_obj);

      int res = m4c0::objc::objc_msg_send<int>(obj, "sumWith:", a);
      AssertThat(res, Is().EqualTo(a + b));
    });
    it("can delegate to virtual methods", [] {
      static constexpr const auto a = 2793;
      static constexpr const auto b = 6279;

      m4c0::objc::autorelease_pool pool;

      const char * cls_name = m4c0::objc::delegated_class_builder<my_virt_cls>("NSObject")
                                  .add_method<&my_virt_cls::add>("sumWith:", "i@:i")
                                  .build();
      auto * obj = create_object(cls_name);

      my_virt_cls my_virt_obj { b };
      m4c0::objc::delegated_class_builder<my_virt_cls>::set_ivar(obj, &my_virt_obj);

      int res = m4c0::objc::objc_msg_send<int>(obj, "sumWith:", a);
      AssertThat(res, Is().EqualTo(a + b));
    });
  });
});
