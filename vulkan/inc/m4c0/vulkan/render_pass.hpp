#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkRenderPass = struct VkRenderPass_T *;

namespace m4c0::vulkan {
  class surface_format;

  struct render_pass : details::handle<VkRenderPass> {
    using handle::handle;
    [[nodiscard]] static render_pass create_with_opiniated_defaults_and_format(const surface_format * sfmt);
  };
}
