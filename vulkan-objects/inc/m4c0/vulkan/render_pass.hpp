#pragma once

#include "m4c0/vulkan/handle.hpp"

struct VkRenderPass_T;

namespace m4c0::vulkan {
  class physical_device;
  class surface;
  class surface_format;

  class render_pass : public details::nd_handle<VkRenderPass_T> {
  public:
    using nd_handle::nd_handle;
    [[nodiscard]] static render_pass create_with_opiniated_defaults_and_format(const surface_format * sfmt);
    [[nodiscard]] static render_pass create_opiniated(const physical_device * pd, const surface * s);
  };
}
