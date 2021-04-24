#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkImage_T;

namespace m4c0::vulkan {
  struct memory_requirements;

  class image : public details::nd_handle<VkImage_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static image create_rgba_with_extent(unsigned w, unsigned h);
    [[nodiscard]] static image create_depth_with_extent(unsigned w, unsigned h);

    [[nodiscard]] memory_requirements memory_requirements() const;
  };
}
