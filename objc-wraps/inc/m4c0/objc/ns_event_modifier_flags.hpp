#pragma once

namespace m4c0::objc {
  enum ns_event_modifier_flags : unsigned {
    // TODO: add remaining options
    // see: https://developer.apple.com/documentation/appkit/nseventmodifierflags
    option = 1U << 17U,
  };
}
