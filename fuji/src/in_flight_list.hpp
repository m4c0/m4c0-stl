#pragma once

#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/in_flight.hpp"

#include <array>

namespace m4c0::fuji {
  class in_flight_list {
    static constexpr auto max_in_flight = 2;

    std::array<in_flight, max_in_flight> m_list;
    unsigned m_current { 0 };

  public:
    explicit in_flight_list(const device_context * ld)
      : m_list { { in_flight { ld->unified_queue_family() }, in_flight { ld->unified_queue_family() } } } {
    }

    [[nodiscard]] m4c0::fuji::in_flight * flip() noexcept {
      m_current = (m_current + 1) % max_in_flight;
      return &m_list[m_current]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
    }
  };
}
