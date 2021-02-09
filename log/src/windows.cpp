#include "m4c0/log.hpp"

#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <tchar.h>
#include <windows.h>

static auto _exe_path() noexcept {
  TCHAR exepath[MAX_PATH + 1];

  if (GetModuleFileName(0, exepath, MAX_PATH + 1) == 0) {
    std::terminate();
  }

  return std::filesystem::path { exepath };
}
static void _log(const char * level, const char * msg) {
  std::time_t t = std::time(nullptr);
  std::tm tm {};
  localtime_s(&tm, &t);

  auto exe = _exe_path();
  std::ofstream out { exe.replace_extension(".log"), std::ios::app };
  out << std::put_time(&tm, "%F %T %z") << " [" << level << "] " << msg << std::endl;
}
void m4c0::log::debug(const char * msg) {
  _log("debug", msg);
}
void m4c0::log::error(const char * msg) {
  _log("error", msg);
}
void m4c0::log::info(const char * msg) {
  _log("info", msg);
}
void m4c0::log::warning(const char * msg) {
  _log("warning", msg);
}
