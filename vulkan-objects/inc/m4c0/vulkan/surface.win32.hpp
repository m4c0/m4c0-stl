#pragma once

#include <windows.h>

namespace m4c0::vulkan {
  class native_provider {
  public:
    [[nodiscard]] virtual HINSTANCE hinstance() const noexcept = 0;
    [[nodiscard]] virtual HWND hwnd() const noexcept = 0;
  };
}
