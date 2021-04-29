#pragma once

#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/log.hpp"
#include "m4c0/vulkan/surface.hpp"

#include <thread>

namespace m4c0::fuji {
  template<class MainLoopTp>
  class main_loop_thread;

  /// \brief Base virtual class to allow type erasure of MainLoopTp
  template<>
  class main_loop_thread<void> {
  public:
    virtual void interrupt() = 0;
    virtual void window_resized(unsigned w, unsigned h) = 0;
  };

  /// \brief Convenience for running a main_loop in a different thread
  template<class MainLoopTp>
  class main_loop_thread : public main_loop_thread<void> {
    MainLoopTp m_loop;
    std::thread m_thread;

  public:
    explicit main_loop_thread(const char * name, vulkan::native_ptr_t native_ptr)
      : m_loop()
      , m_thread(&main_loop::run_global, &m_loop, name, native_ptr) {
      m4c0::log::info("Vulkan thread starting");
    }

    void interrupt() override {
      m_loop.interrupt();
      m_thread.join();
    }
    void window_resized(unsigned w, unsigned h) override {
      m_loop.window_resized(w, h);
    }
  };
}
