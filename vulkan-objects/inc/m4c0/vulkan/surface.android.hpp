#pragma once

class ANativeWindow;

namespace m4c0::vulkan {
  class native_provider {
  public:
    [[nodiscard]] virtual ANativeWindow * window() const noexcept = 0;
  };
}
