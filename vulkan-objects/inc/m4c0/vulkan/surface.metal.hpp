#pragma once

using CAMetalLayer = void;

namespace m4c0::vulkan {
  class native_provider {
  public:
    [[nodiscard]] virtual CAMetalLayer * layer() const noexcept = 0;
  };
}
