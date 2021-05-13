#pragma once

#include "m4c0/fifo_worker.hpp"
#include "m4c0/native_handles.hpp"
#include "m4c0/vulkan/extent_2d.hpp"

using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::fuji {
  class device_context;
  class swapchain_context;

  struct main_loop_listener {
    virtual void build_primary_command_buffer(VkCommandBuffer cb) = 0;
    virtual void build_secondary_command_buffer(VkCommandBuffer cb) = 0;
    virtual void on_render_extent_change(vulkan::extent_2d e) = 0;
  };

  class main_loop {
    class interrupted_exception : public std::exception {};

    m4c0::fifo_worker<> m_notifications {};
    main_loop_listener * m_listener {};

  protected:
    virtual void run_extent(const device_context * ld, const swapchain_context * sc);
    virtual void run_device(const device_context * ld);

    [[nodiscard]] main_loop_listener *& listener() noexcept {
      return m_listener;
    }

  public:
    void interrupt();

    virtual void run_global(const char * name, const native_handles * np);
  };

  template<class StuffTp>
  class main_loop_with_stuff : public main_loop {
  public:
    void run_device(const device_context * ld) override {
      StuffTp s { ld };
      listener() = &s;

      main_loop::run_device(ld);
    }
  };
}
