#pragma once

#include "m4c0/fifo_worker.hpp"
#include "m4c0/function.hpp"

using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::vulkan {
  class native_provider;
}

namespace m4c0::fuji {
  class device_context;
  class swapchain_context;

  class main_loop {
    class interrupted_exception : public std::exception {};

    m4c0::fifo_worker<> m_notifications {};
    m4c0::function<void(VkCommandBuffer)> m_primary_cbb {};
    m4c0::function<void(VkCommandBuffer)> m_secondary_cbb {};

  protected:
    virtual void run_extent(const device_context * ld, const swapchain_context * sc);
    virtual void run_device(const device_context * ld);

    template<typename Fn>
    void set_primary_cbb(Fn && fn) {
      m_primary_cbb = std::forward<Fn>(fn);
    }
    template<typename Fn>
    void set_secondary_cbb(Fn && fn) {
      m_secondary_cbb = std::forward<Fn>(fn);
    }

  public:
    void interrupt();

    virtual void run_global(const char * name, const vulkan::native_provider * np);
  };
}
