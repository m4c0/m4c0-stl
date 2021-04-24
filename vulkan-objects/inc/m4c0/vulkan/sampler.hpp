#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkSampler_T;

namespace m4c0::vulkan {
  class sampler : public details::nd_handle<VkSampler_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static sampler create_with_opiniated_defaults();
  };
}
