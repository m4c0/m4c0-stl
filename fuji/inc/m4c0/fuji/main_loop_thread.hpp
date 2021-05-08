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
    template<typename... Args>
    void start(Args &&... args) {
      if (m_thread.joinable()) {
        interrupt();
      }
      m_thread = std::thread { &MainLoopTp::run_global, &m_loop, std::forward<Args>(args)... };
      m4c0::log::info("Vulkan thread starting");
    }

    void interrupt() {
      m4c0::log::info("Vulkan thread ending");
      m_loop.interrupt();
      m_thread.join();
    }
  };
}
