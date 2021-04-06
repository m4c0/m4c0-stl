#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkImage = struct VkImage_T *;

namespace m4c0::vulkan {
  struct image : details::handle<VkImage> {
    using handle::handle;
    [[nodiscard]] static image create_rgba_with_extent(unsigned w, unsigned h);
    [[nodiscard]] static image create_depth_with_extent(unsigned w, unsigned h);
  };
}
