#include "m4c0/test.hpp"

#include <objc/message.h>
#include <objc/runtime.h>
#include <string>
#include <unordered_map>

template<class Ret>
static Ret objc_msg_send(void * obj, const char * sel_name) {
  SEL sel = sel_getUid(sel_name);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  return reinterpret_cast<Ret (*)(void *, SEL)>(objc_msgSend)(obj, sel);
}

class autorelease_pool {
  id m_ar;

  static auto objc_new() {
    auto * ar_cls = objc_getClass("NSAutoreleasePool");
    return objc_msg_send<id>(ar_cls, "new");
  }

public:
  autorelease_pool() : m_ar(objc_new()) {
  }
  ~autorelease_pool() {
    objc_msg_send<void>(m_ar, "drain");
  }

  autorelease_pool(autorelease_pool &&) = delete;
  autorelease_pool(const autorelease_pool &) = delete;
  autorelease_pool & operator=(autorelease_pool &&) = delete;
  autorelease_pool & operator=(const autorelease_pool &) = delete;
};

namespace m4c0::objc {
  class middleware {
    std::unordered_map<const char *, Class> m_class_cache {};
    std::unordered_map<const char *, IMP> m_imps {};

    Class create_class(const char * base_class_name) {
      using namespace std::literals;
      std::string name = "M4C0_$$_"s + base_class_name;
      Class super = objc_getClass(base_class_name);
      Class cls = objc_allocateClassPair(super, name.c_str(), 0);
      for (auto & kv : m_imps) {
        Method m = class_getInstanceMethod(super, sel_getUid(kv.first));
        if (m == nullptr) continue;

        const char * sign = method_getTypeEncoding(m);
        SEL sel = sel_getUid(kv.first);
        class_addMethod(cls, sel, kv.second, sign);
      }
      objc_registerClassPair(cls);
      return cls;
    }
    Class get_class(const char * base_class_name) {
      auto & cls = m_class_cache[base_class_name];
      if (cls == nullptr) cls = create_class(base_class_name);
      return cls;
    }

  public:
    static middleware & instance() {
      static middleware i {};
      return i;
    }
    middleware() = default;
    ~middleware() {
      for (auto & kv : m_class_cache) {
        objc_disposeClassPair(kv.second);
      }
    }

    middleware(middleware &&) = delete;
    middleware(const middleware &) = delete;
    middleware & operator=(middleware &&) = delete;
    middleware & operator=(const middleware &) = delete;

    void * create_for(const char * base_class_name) {
      Class cls = get_class(base_class_name);
      void * result = objc_msg_send<void *>(cls, "new");
      return objc_msg_send<void *>(result, "autorelease");
    }
    template<typename Ret, typename... Args>
    void add_forward(const char * sel_name, Ret (*fn)(Args...)) {
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      IMP imp = *reinterpret_cast<IMP *>(&fn);
      m_imps[sel_name] = imp;
    }
  };
}

static auto dummy() {
  return 3;
}

go_bandit([] { // NOLINT
  describe("objc-bridge", [] {
    it("can create an autorelease pool", [] {
      autorelease_pool pool;
    });
    it("creates instances of a base class", [] {
      m4c0::objc::middleware midware;
      autorelease_pool pool;

      void * obj = midware.create_for("NSObject");
      AssertThat(obj, Is().Not().Null());
    });
    it("creates instances of a base class a second time", [] {
      // This validates if next tests will have a chance of succeeding
      m4c0::objc::middleware midware;
      autorelease_pool pool;

      void * obj = midware.create_for("NSObject");
      AssertThat(obj, Is().Not().Null());
    });
    it("can invoke methods from the base class", [] {
      m4c0::objc::middleware midware;
      autorelease_pool pool;

      void * obj = midware.create_for("NSObject");
      void * str = objc_msg_send<void *>(obj, "className");
      const char * cstr = objc_msg_send<const char *>(str, "UTF8String");
      AssertThat(cstr, Is().EqualTo("M4C0_$$_NSObject"));
    });
    it("override methods", [] {
      m4c0::objc::middleware midware;
      midware.add_forward("length", &dummy);

      autorelease_pool pool;

      void * obj = midware.create_for("NSString");
      int res = objc_msg_send<int>(obj, "length");
      AssertThat(res, Is().EqualTo(dummy()));
    });
  });
});
