#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkDevice = struct VkDevice_T *;
using VkQueue = struct VkQueue_T *;

namespace m4c0::vulkan {
  class physical_device;

  class device : details::handle<VkDevice> {
    VkQueue m_unified_queue;

    explicit constexpr device(VkDevice d, VkQueue q) : handle(d), m_unified_queue(q) {
    }

  public:
    using handle::handle;
    device(VkDevice) = delete;

    [[nodiscard]] static device create_for_physical_device(const physical_device * pd);

    [[nodiscard]] constexpr VkQueue unified_queue() const {
      return m_unified_queue;
    }

    void wait_idle() const noexcept;
  };
}
