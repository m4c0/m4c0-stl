#pragma once

#include "m4c0/objc/geometry.hpp"
#include "m4c0/objc/ns_event_type.hpp"
#include "m4c0/objc/ns_object.hpp"

namespace m4c0::objc {
  class ns_event : public ns_object {
  public:
    explicit ns_event(void * obj) : ns_object(obj) {
    }

    [[nodiscard]] cg_point location_in_window() const {
      return get<cg_point>("locationInWindow");
    }

    [[nodiscard]] ns_event_type type() const {
      return static_cast<ns_event_type>(get<unsigned>("type"));
    }
  };
}
