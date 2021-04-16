#pragma once

#include "m4c0/vulkan/handle.hpp"

#include <vector>

struct VkImage_T;
struct VkSwapchainKHR_T;

namespace m4c0::vulkan {
  class physical_device;
  class semaphore;
  class surface;

  struct swapchain : details::nd_handle<VkSwapchainKHR_T> {
    using nd_handle::nd_handle;
    [[nodiscard]] static swapchain best_for(const physical_device * pd, const surface * s, unsigned w, unsigned h);

    [[nodiscard]] unsigned acquire_next_image(const semaphore * sem) const;
    [[nodiscard]] std::vector<details::pointer_t<VkImage_T>> get_images() const;
  };
}
