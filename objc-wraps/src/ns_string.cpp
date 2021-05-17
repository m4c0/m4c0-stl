#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_string.hpp"

using namespace m4c0::objc;

ns_string ns_string::with_cstring_utf8(const char * c_str) {
  // https://developer.apple.com/documentation/foundation/1497293-string_encodings/nsutf8stringencoding?language=objc
  constexpr const auto utf8_encoding = 4;

  ns_object res { "NSString", "alloc" };
  void * obj = objc_msg_send<void *>(res.self(), "initWithCString:encoding:", c_str, utf8_encoding);
  return ns_string { "NSString", obj };
}
