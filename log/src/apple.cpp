#include "m4c0/log.hpp"

extern "C" void m4c0_log(const char *, const char *);

void m4c0::log::debug(const char * msg) {
  m4c0_log("debug", msg);
}
void m4c0::log::error(const char * msg) {
  m4c0_log("error", msg);
}
void m4c0::log::info(const char * msg) {
  m4c0_log("info", msg);
}
void m4c0::log::warning(const char * msg) {
  m4c0_log("warning", msg);
}
