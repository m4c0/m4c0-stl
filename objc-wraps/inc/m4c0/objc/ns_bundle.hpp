#pragma once

#include "m4c0/objc/ns_object.hpp"
#include "m4c0/objc/ns_string.hpp"

namespace m4c0::objc {
  class ns_bundle : public ns_object {
    using ns_object::ns_object;

  public:
    // Shortcut for [[this infoDictionary] objectForKey:@"CFBundleName"]
    [[nodiscard]] ns_string bundle_name();

    [[nodiscard]] static ns_bundle main_bundle();
  };
}
