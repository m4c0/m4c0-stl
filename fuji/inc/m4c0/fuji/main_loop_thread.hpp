#pragma once

#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/log.hpp"
#include "m4c0/vulkan/surface.hpp"

#include <thread>

namespace m4c0::fuji {
  /// \brief Convenience for running a main_loop in a different thread
  template<class MainLoopTp>
  class main_loop_thread {
    MainLoopTp m_loop;
    std::thread m_thread;

  public:
    explicit main_loop_thread(const char * name, vulkan::native_ptr_t native_ptr)
      : m_loop()
      , m_thread(&main_loop::run_global, &m_loop, name, native_ptr) {
      m4c0::log::info("Vulkan thread starting");
    }

    void interrupt() {
      m_loop.interrupt();
      m_thread.join();
    }
    void window_resized(unsigned w, unsigned h) {
      m_loop.window_resized(w, h);
    }
  };
}
