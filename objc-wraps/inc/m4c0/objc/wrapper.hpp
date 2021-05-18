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
      object_set_ivar(Base::self(), builder_t::cpp_ivar_name, this);
    }
  };
}
