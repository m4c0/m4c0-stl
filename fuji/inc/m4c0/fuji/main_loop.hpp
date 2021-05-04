#pragma once

#include "m4c0/fifo_worker.hpp"

struct VkCommandBuffer_T;

namespace m4c0::vulkan {
  class native_provider;
}

namespace m4c0::fuji {
  class device_context;
  class frame_context;
  class in_flight;
  class swapchain_context;

  class main_loop {
    class interrupted_exception : public std::exception {};

    m4c0::fifo_worker<> m_notifications {};

  protected:
    using cmd_buf = struct VkCommandBuffer_T *;

    virtual void build_primary(cmd_buf cb) = 0;
    virtual void build_secondary(cmd_buf cb) = 0;

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

    virtual void run_global(const char * name, const vulkan::native_provider * np);
  };
}
