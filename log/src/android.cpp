#include "m4c0/log.hpp"

#include <android/log.h>

void m4c0::log::debug(const char * msg) {
  __android_log_print(ANDROID_LOG_DEBUG, "m4c0", "%s", msg);
}
void m4c0::log::error(const char * msg) {
  __android_log_print(ANDROID_LOG_ERROR, "m4c0", "%s", msg);
}
void m4c0::log::info(const char * msg) {
  __android_log_print(ANDROID_LOG_INFO, "m4c0", "%s", msg);
}
void m4c0::log::warning(const char * msg) {
  __android_log_print(ANDROID_LOG_WARN, "m4c0", "%s", msg);
}
