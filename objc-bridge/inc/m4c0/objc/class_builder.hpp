#pragma once

#include "m4c0/objc/casts.hpp"

namespace m4c0::objc {
  using imp_t = void (*)();

  class class_builder {
    void * m_class;

  public:
    explicit class_builder(const char * parent);

    class_builder & add_ivar(const char * name, unsigned size, unsigned align, const char * sign);
    class_builder & add_ptr_ivar(const char * name) {
      return add_ivar(name, sizeof(void *), alignof(void *), "@");
    }

    class_builder & add_method(const char * sel, imp_t imp, const char * sign);
    template<typename Fn>
    class_builder & add_method(const char * sel, Fn && fn, const char * sign) {
      return add_method(sel, to_imp(fn), sign);
    }

    // static const auto * cls_name = class_builder(...).add(...).build();
    const char * build();
  };
}
