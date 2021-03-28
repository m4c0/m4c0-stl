#pragma once

#include "m4c0/pimpl.hpp"

namespace m4c0::objc {
  class middleware {
    class data;
    pimpl<data> m_data {};

    void add_imp(const char * sel_name, void (*imp)());

  public:
    static middleware & instance() {
      static middleware i {};
      return i;
    }
    middleware() = default;
    ~middleware();

    middleware(middleware &&) = delete;
    middleware(const middleware &) = delete;
    middleware & operator=(middleware &&) = delete;
    middleware & operator=(const middleware &) = delete;

    void * create_for(const char * base_class_name);
    template<typename Fn>
    void add_forward(const char * sel_name, Fn fn) {
      add_imp(sel_name, to_imp(fn));
    }
  };
}
