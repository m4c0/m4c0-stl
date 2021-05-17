#pragma once

namespace m4c0::objc {
  enum class ns_event_modifier_flags : unsigned {
    // TODO: add remaining options
    // see: https://developer.apple.com/documentation/appkit/nseventmodifierflags
    option = 1U << 17U,
  };

  static ns_event_modifier_flags operator|(ns_event_modifier_flags lhs, ns_event_modifier_flags rhs) {
    return static_cast<ns_event_modifier_flags>(static_cast<unsigned>(lhs) | static_cast<unsigned>(rhs));
  }
}
