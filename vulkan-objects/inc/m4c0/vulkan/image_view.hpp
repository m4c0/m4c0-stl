#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkImageView_T;
struct VkImage_T;

namespace m4c0::vulkan {
  class image;
  class surface_format;

  struct image_view : details::nd_handle<VkImageView_T> {
    using nd_handle::nd_handle;
    [[nodiscard]] static image_view create_rgba_for_image_and_format(
        details::pointer_t<VkImage_T> img,
        const surface_format * sfmt);
    [[nodiscard]] static image_view create_rgba_for_image(const image * img);
    [[nodiscard]] static image_view create_depth_for_image(const image * img);
  };
}
