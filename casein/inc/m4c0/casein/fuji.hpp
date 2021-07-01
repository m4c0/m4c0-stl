#pragma once

#include "m4c0/casein/main.hpp"
#include "m4c0/fuji/main_loop_thread.hpp"
#include "m4c0/native_handles.hpp"

namespace m4c0::casein {
  template<class Tp>
  class fuji_handler : public handler {
    fuji::main_loop_thread<Tp> m_stuff {};
    const native_handles * m_nh;

  public:
    explicit fuji_handler(const native_handles * nh) : m_nh(nh) {
      m_stuff.start(nh);
    }
    ~fuji_handler() override {
      m_stuff.interrupt();
    }

    fuji_handler(fuji_handler &&) = delete;
    fuji_handler(const fuji_handler &) = delete;
    fuji_handler & operator=(fuji_handler &&) = delete;
    fuji_handler & operator=(const fuji_handler &) = delete;
  };
}
