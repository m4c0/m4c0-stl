#pragma once

#include "m4c0/vulkan/handle.hpp"

using VkImage = struct VkImage_T *;
using VkImageView = struct VkImageView_T *;

namespace m4c0::vulkan {
  class image;
  class surface_format;

  struct image_view : details::handle<VkImageView> {
    using handle::handle;
    [[nodiscard]] static image_view create_rgba_for_image_and_format(VkImage img, const surface_format * sfmt);
    [[nodiscard]] static image_view create_rgba_for_image(const image * img);
    [[nodiscard]] static image_view create_depth_for_image(const image * img);
  };
}
