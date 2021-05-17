#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_string : public ns_object {
    using ns_object::ns_object;

  public:
    static ns_string with_cstring_utf8(const char * c_str);
  };
}
