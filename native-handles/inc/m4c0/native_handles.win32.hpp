#pragma once

#include <windows.h>

namespace m4c0 {
  class native_handles {
  public:
    [[nodiscard]] virtual HINSTANCE hinstance() const noexcept = 0;
    [[nodiscard]] virtual HWND hwnd() const noexcept = 0;
  };
}
