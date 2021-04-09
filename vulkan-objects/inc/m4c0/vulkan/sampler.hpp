#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkSampler = struct VkSampler_T *;

namespace m4c0::vulkan {
  struct sampler : details::handle<VkSampler> {
    using handle::handle;
    [[nodiscard]] static sampler create_with_opiniated_defaults();
  };
}
