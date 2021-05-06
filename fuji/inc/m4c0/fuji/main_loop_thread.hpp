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
    void start(const char * name, const vulkan::native_provider * native_ptr) {
      if (m_thread.joinable()) {
        interrupt();
      }
      m_thread = std::thread { &main_loop::run_global, &m_loop, name, native_ptr };
      m4c0::log::info("Vulkan thread starting");
    }

    void interrupt() {
      m4c0::log::info("Vulkan thread ending");
      m_loop.interrupt();
      m_thread.join();
    }
  };
}
