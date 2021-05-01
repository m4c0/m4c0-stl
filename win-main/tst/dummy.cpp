#include "m4c0/win/main.hpp"

LRESULT CALLBACK m4c0::win::window_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
  return DefWindowProc(hwnd, msg, w_param, l_param);
}
