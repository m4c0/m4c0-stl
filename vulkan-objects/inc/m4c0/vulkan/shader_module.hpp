#pragma once

#include "m4c0/vulkan/handle.hpp"

#include <cstdint>
#include <span>

struct VkShaderModule_T;

namespace m4c0::vulkan {
  class shader_module : public details::nd_handle<VkShaderModule_T> {
  public:
    using nd_handle::nd_handle;

    [[nodiscard]] static shader_module create_from_spv(std::span<const std::uint32_t> spv);
  };
}
