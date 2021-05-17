#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_string.hpp"

using namespace m4c0::objc;

// https://developer.apple.com/documentation/foundation/1497293-string_encodings/nsutf8stringencoding?language=objc
constexpr const auto utf8_encoding = 4;

ns_string ns_string::with_cstring_utf8(const char * c_str) {
  Class cls = objc_getClass("NSString");

  void * obj = objc_msg_send<void *>(cls, "stringWithCString:encoding:", c_str, utf8_encoding);
  return ns_string { obj };
}

const char * ns_string::c_string_using_utf8() {
  return objc_msg_send<const char *>(self(), "cStringUsingEncoding:", utf8_encoding);
}
