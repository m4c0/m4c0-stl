#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkPhysicalDevice = struct VkPhysicalDevice_T *;

namespace m4c0::vulkan {
  class surface;

  class physical_device {
    VkPhysicalDevice m_handle;
    /** ID of the queue family that supports all command types */
    int m_unified_queue_family;

    constexpr physical_device(VkPhysicalDevice pd, int q) : m_handle(pd), m_unified_queue_family(q) {
    }

  public:
    [[nodiscard]] static physical_device best_for(const surface *);

    [[nodiscard]] constexpr VkPhysicalDevice pointer() const {
      return m_handle;
    }
    [[nodiscard]] constexpr int unified_queue_family() const {
      return m_unified_queue_family;
    }
  };
}
