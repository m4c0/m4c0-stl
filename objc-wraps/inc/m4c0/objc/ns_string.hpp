#pragma once

#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_string : public ns_object {
    using ns_object::ns_object;

  public:
    explicit ns_string(void * o) : ns_object(o) {
    }

    [[nodiscard]] const char * c_string_using_utf8();

    [[nodiscard]] static ns_string with_cstring_utf8(const char * c_str);
  };
}
