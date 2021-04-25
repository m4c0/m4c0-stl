#pragma once

#include "m4c0/vulkan/extent_2d.hpp"
#include "m4c0/vulkan/handle.hpp"

#include <vector>

struct VkFramebuffer_T;
struct VkImageView_T;

namespace m4c0::vulkan {
  class image_view;
  class render_pass;

  class framebuffer : public details::nd_handle<VkFramebuffer_T> {
  public:
    class builder {
      unsigned m_width;
      unsigned m_height;
      const render_pass * m_render_pass;
      std::vector<details::pointer_t<VkImageView_T>> m_attachments {};

    public:
      [[nodiscard]] builder & with_extent(unsigned w, unsigned h) {
        m_width = w;
        m_height = h;
        return *this;
      }
      [[nodiscard]] builder & with_extent(extent_2d e) {
        return with_extent(e.width(), e.height());
      }
      [[nodiscard]] builder & with_render_pass(const render_pass * rp) {
        m_render_pass = rp;
        return *this;
      }
      [[nodiscard]] builder & add_attachment(const image_view * iv);

      [[nodiscard]] framebuffer build() const;
    };

    using nd_handle::nd_handle;
  };
}
