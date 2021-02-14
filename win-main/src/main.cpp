#include "m4c0/win/main.hpp"

#include <exception>
#include <stdexcept>
#include <tchar.h>
#include <windows.h>

static constexpr const auto window_class = "m4c0-window-class";

static void register_class(HINSTANCE h_instance) {
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = m4c0::win::window_proc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = h_instance;
  wcex.hIcon = LoadIcon(h_instance, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = _T(window_class);
  wcex.hIconSm = LoadIcon(h_instance, IDI_APPLICATION);

  if (!RegisterClassEx(&wcex)) {
    throw std::runtime_error("Failed to register class");
  }
}

static void create_window(HINSTANCE h_instance, int show) {
  auto hwnd = CreateWindow(
      _T(window_class),
      _T(m4c0::win::window_title()),
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      800,
      600,
      NULL,
      NULL,
      h_instance,
      NULL);
  if (!hwnd) throw std::runtime_error("Failed to create window");

  ShowWindow(hwnd, show);
  UpdateWindow(hwnd);
}

static int main_loop() {
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return static_cast<int>(msg.wParam);
}

int CALLBACK WinMain(
    _In_ HINSTANCE h_instance,
    _In_opt_ HINSTANCE /* unused */,
    _In_ LPSTR /* command line */,
    _In_ int cmd_show) try {
  register_class(h_instance);
  create_window(h_instance, cmd_show);
  return main_loop();
} catch (const std::exception & e) {
  MessageBox(NULL, _T(e.what()), _T(m4c0::win::window_title()), NULL);
  return 1;
}
