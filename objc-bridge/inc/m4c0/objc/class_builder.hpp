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
    [[nodiscard]] const char * build();
  };

  template<class Tp>
  class delegated_class_builder {
    class_builder m_builder;

    template<typename M>
    struct wrap;
    template<typename Ret, typename... Args>
    struct wrap<Ret (Tp::*)(Args...)> {
      template<auto M>
      static auto call(void * self, void * /*sel*/, Args... args) -> Ret {
        // This can't be a perfect forward due to objc shenanigans
        return (object_get_ivar<Tp *>(self, cpp_ivar_name)->*M)(args...);
      }
    };

  public:
    static constexpr const auto cpp_ivar_name = "m4c0_$$_cpp";

    explicit delegated_class_builder(const char * parent) : m_builder(parent) {
      m_builder.add_ptr_ivar(cpp_ivar_name);
    }

    template<auto M>
    delegated_class_builder & add_method(const char * sel, const char * sign) {
      auto wrapper = wrap<decltype(M)>::template call<M>;
      m_builder.add_method(sel, wrapper, sign);
      return *this;
    }

    [[nodiscard]] auto build() {
      return m_builder.build();
    }
  };
}
