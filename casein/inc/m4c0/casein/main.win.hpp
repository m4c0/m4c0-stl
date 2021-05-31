#pragma once

#include "m4c0/casein/main.hpp"
#include "m4c0/native_handles.win32.hpp"
#include "m4c0/win/main.hpp"

namespace m4c0::casein::win {
  class wnd_provider : public m4c0::vulkan::native_provider {
    HWND m_hwnd;

  public:
    explicit constexpr wnd_provider(HWND hwnd) : m_hwnd(hwnd) {
    }
    [[nodiscard]] HINSTANCE hinstance() const noexcept override {
      return GetModuleHandle(nullptr);
    }
    [[nodiscard]] HWND hwnd() const noexcept override {
      return m_hwnd;
    }
  };

  static LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    static wnd_provider wp { hwnd };
    static std::unique_ptr<m4c0::casein::handler> h;

    switch (msg) {
    case WM_CREATE:
      h = m4c0::casein::main(&wp);
      return 0;
    case WM_DESTROY:
      h.reset();
      PostQuitMessage(0);
      return 0;
    }

    return DefWindowProc(hwnd, msg, w_param, l_param);
  }
}
