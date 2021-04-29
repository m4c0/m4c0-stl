#pragma once

#include "m4c0/fifo_worker.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/vulkan/command_buffer_guard.hpp"
#include "m4c0/vulkan/surface.hpp"

namespace m4c0::fuji {
  class device_context;
  class frame_context;
  class in_flight;
  class swapchain_context;

  class main_loop {
    using cmd_buf = VkCommandBuffer;

    class interrupted_exception : public std::exception {};

    m4c0::fifo_worker<> m_notifications {};
    std::atomic_uint32_t m_window_width {};
    std::atomic_uint32_t m_window_height {};

    virtual void build_primary(cmd_buf cb) {
    }
    virtual void build_secondary(cmd_buf cb) {
    }

    cmd_buf run_primary(
        const device_context * ld,
        const swapchain_context * sc,
        const frame_context * f,
        main_loop::cmd_buf secondary);
    cmd_buf run_secondary(const device_context * ld, const in_flight * inf);
    virtual void run_frame(const device_context * ld, const swapchain_context * sc, const in_flight * inf);
    virtual void run_extent(const device_context * ld, const swapchain_context * sc);
    virtual void run_device(const device_context * ld);

  public:
    void interrupt();
    void window_resized(unsigned w, unsigned h);
    virtual void run_global(const char * name, vulkan::native_ptr_t native_ptr);
  };
}
