#pragma once

#include "m4c0/objc/class_builder.hpp"

namespace m4c0::objc {
  template<class Self, class Base>
  class wrapper : public Base {
    using builder_t = delegated_class_builder<Self>;
    using builder_fn_t = builder_t (*)();

    static const char * get_class_name(builder_fn_t fn) {
      static const char * class_name = fn().build();
      return class_name;
    }

  protected:
    explicit wrapper(builder_fn_t fn) : Base(get_class_name(fn)) {
      builder_t::set_ivar(Base::self(), static_cast<Self *>(this));
    }

  public:
    ~wrapper() {
      builder_t::set_ivar(Base::self(), static_cast<Self *>(nullptr));
    }

    wrapper(const wrapper &) = delete;
    wrapper(wrapper &&) = delete;
    wrapper & operator=(const wrapper &) = delete;
    wrapper & operator=(wrapper &&) = delete;
  };
}
