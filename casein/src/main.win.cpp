#include "m4c0/casein/main.win.hpp"
#include "m4c0/win/main.hpp"

LRESULT CALLBACK m4c0::win::window_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
  return m4c0::casein::win::window_proc(hwnd, msg, w_param, l_param);
}
