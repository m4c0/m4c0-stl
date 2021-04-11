#pragma once

#include "m4c0/vulkan/handle.hpp"

#include <vector>

using VkFramebuffer = struct VkFramebuffer_T *;
using VkImageView = struct VkImageView_T *;

namespace m4c0::vulkan {
  class image_view;
  class render_pass;

  struct framebuffer : details::handle<VkFramebuffer> {
    class builder {
      unsigned m_width;
      unsigned m_height;
      const render_pass * m_render_pass;
      std::vector<VkImageView> m_attachments {};

    public:
      [[nodiscard]] builder & with_extent(unsigned w, unsigned h) {
        m_width = w;
        m_height = h;
        return *this;
      }
      [[nodiscard]] builder & with_render_pass(const render_pass * rp) {
        m_render_pass = rp;
        return *this;
      }
      [[nodiscard]] builder & add_attachment(const image_view * iv);

      [[nodiscard]] framebuffer build() const;
    };

    using handle::handle;
  };
}