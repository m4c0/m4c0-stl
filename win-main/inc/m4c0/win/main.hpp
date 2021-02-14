#pragma once

#include <windows.h>

// TODO: Improve this interface
namespace m4c0::win {
  const char * window_title();
  LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
}
