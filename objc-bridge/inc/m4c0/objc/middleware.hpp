#pragma once

#include "m4c0/pimpl.hpp"

namespace m4c0::objc {
  class middleware {
    class data;
    pimpl<data> m_data {};

  public:
    using imp_t = void (*)();

    static middleware & instance() {
      static middleware i {};
      return i;
    }
    middleware();
    ~middleware();

    middleware(middleware &&) = delete;
    middleware(const middleware &) = delete;
    middleware & operator=(middleware &&) = delete;
    middleware & operator=(const middleware &) = delete;

    void * create_for(const char * base_class_name);
    void add_imp(const char * sel_name, imp_t imp);
  };
}
