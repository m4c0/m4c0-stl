#pragma once

#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/fuji/swapchain_context.hpp"

namespace m4c0::fuji {
  class frames_list {
    std::vector<frame_context> m_frames;

  public:
    frames_list(const device_context * ld, const swapchain_context * sc) {
      unsigned i = 0;
      for (vulkan::details::pointer_t<VkImage_T> img : sc->images()) {
        m_frames.emplace_back(ld, sc, img, i++);
      }
    }

    [[nodiscard]] const frame_context * at(unsigned index) const noexcept {
      return &m_frames.at(index);
    }
  };
}
