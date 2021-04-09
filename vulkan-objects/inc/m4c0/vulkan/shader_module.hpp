#pragma once

#include "m4c0/vulkan/handle.hpp"

#include <cstdint>
#include <span>

using VkShaderModule = struct VkShaderModule_T *;

namespace m4c0::vulkan {
  struct shader_module : details::handle<VkShaderModule> {
    using handle::handle;

    [[nodiscard]] static shader_module create_from_spv(std::span<const std::uint32_t> spv);
  };
}
