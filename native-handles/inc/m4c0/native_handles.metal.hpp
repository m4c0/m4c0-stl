#pragma once

using CAMetalLayer = void;

namespace m4c0 {
  class native_handles {
  public:
    [[nodiscard]] virtual CAMetalLayer * layer() const noexcept = 0;
  };
}
