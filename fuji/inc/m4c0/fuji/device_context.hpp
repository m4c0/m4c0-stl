#pragma once

#include "m4c0/vulkan/logical_device.hpp"
#include "m4c0/vulkan/surface.hpp"

namespace m4c0::vulkan {
  class buffer;
  class device_memory;
  class image;
}
namespace m4c0::fuji {
  class device_context : public vulkan::tools::logical_device {
    m4c0::vulkan::render_pass m_render_pass;

  public:
    device_context(const char * app_name, vulkan::native_ptr_t native_ptr)
      : m4c0::vulkan::tools::logical_device(app_name, native_ptr)
      , m_render_pass(best_render_pass()) {
    }
    [[nodiscard]] m4c0::vulkan::device_memory create_local_memory(const m4c0::vulkan::image * img) const;
    [[nodiscard]] m4c0::vulkan::device_memory create_host_memory(const m4c0::vulkan::buffer * img) const;

    [[nodiscard]] constexpr const auto * render_pass() const noexcept {
      return &m_render_pass;
    }
  };
}
