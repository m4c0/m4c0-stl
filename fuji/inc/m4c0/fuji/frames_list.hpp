#pragma once

#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/fuji/swapchain_context.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

namespace m4c0::fuji {
  class frames_list {
    std::vector<frame_context> m_frames;

  public:
    frames_list(const device_context * ld, const swapchain_context * sc) {
      auto images = sc->images();
      std::transform(images.begin(), images.end(), std::back_inserter(m_frames), [ld, sc](auto img) {
        return frame_context(ld, sc, img);
      });
    }

    [[nodiscard]] const frame_context * at(unsigned index) const noexcept {
      return &m_frames.at(index);
    }
  };
}
