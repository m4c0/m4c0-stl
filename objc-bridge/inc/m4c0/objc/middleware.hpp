#pragma once

#include "m4c0/objc/casts.hpp"

#include <objc/message.h>
#include <objc/runtime.h>
#include <string>
#include <unordered_map>

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

    void add_imp(const char * sel_name, void (*imp)()) {
      m_imps[sel_name] = imp;
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
    template<typename Fn>
    void add_forward(const char * sel_name, Fn fn) {
      add_imp(sel_name, to_imp(fn));
    }
  };
}
