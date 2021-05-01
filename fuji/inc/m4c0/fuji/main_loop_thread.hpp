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
    virtual void start(const char * name, vulkan::native_ptr_t native_ptr) = 0;
    virtual void interrupt() = 0;
  };

  /// \brief Convenience for running a main_loop in a different thread
  template<class MainLoopTp>
  class main_loop_thread : public main_loop_thread<void> {
    MainLoopTp m_loop;
    std::thread m_thread;

  public:
    void start(const char * name, vulkan::native_ptr_t native_ptr) override {
      if (m_thread.joinable()) {
        interrupt();
      }
      m_thread = std::thread { &main_loop::run_global, &m_loop, name, native_ptr };
      m4c0::log::info("Vulkan thread starting");
    }

    void interrupt() override {
      m4c0::log::info("Vulkan thread ending");
      m_loop.interrupt();
      m_thread.join();
    }
  };
}
