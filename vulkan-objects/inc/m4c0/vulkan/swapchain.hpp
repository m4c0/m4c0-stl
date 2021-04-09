#pragma once

#include "m4c0/vulkan/handle.hpp"

#include <vector>

using VkImage = struct VkImage_T *;
using VkSwapchainKHR = struct VkSwapchainKHR_T *;

namespace m4c0::vulkan {
  class physical_device;
  class semaphore;
  class surface;

  struct swapchain : details::handle<VkSwapchainKHR> {
    class out_of_date_error {};

    using handle::handle;
    [[nodiscard]] static swapchain best_for(const physical_device * pd, const surface * s, unsigned w, unsigned h);

    [[nodiscard]] unsigned acquire_next_image(const semaphore * sem) const;
    [[nodiscard]] std::vector<VkImage> get_images() const;
  };
}
