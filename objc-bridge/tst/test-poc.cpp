#include "m4c0/test.hpp"

#include <objc/message.h>
#include <objc/runtime.h>

template<class Ret>
Ret objc_msg_send(void * obj, const char * sel_name) {
  SEL sel = sel_getUid(sel_name);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  return reinterpret_cast<Ret (*)(void *, SEL)>(objc_msgSend)(obj, sel);
}

class autorelease_pool {
  id m_ar;

  static auto objc_new() {
    auto * ar_cls = objc_getClass("NSAutorelease");
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
  public:
    static middleware & instance() {
      static middleware i {};
      return i;
    }

    void * create_for(const char * base_class_name) {
      return nullptr;
    }
    template<typename Fn>
    void add_forward(const char * sel_name, Fn fn) {
    }
  };
}

go_bandit([] { // NOLINT
  describe("objc-bridge", [] {
    it("can create an autorelease pool, for no reason", [] {
      autorelease_pool pool;
    });
    it("works", [] {
      autorelease_pool pool;

      auto midware = m4c0::objc::middleware::instance();
      void * obj = midware.create_for("NSObject");

      constexpr auto expected = 3;
      midware.add_forward("draw", [e = expected]() -> int {
        return e;
      });

      int res = objc_msg_send<int>(obj, "draw");
      AssertThat(res, Is().EqualTo(expected));
    });
  });
});
