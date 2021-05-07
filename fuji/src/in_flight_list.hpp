#pragma once

#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/in_flight.hpp"

#include <memory>

namespace m4c0::fuji {
  class in_flight_list {
    std::unique_ptr<in_flight> m_front;
    std::unique_ptr<in_flight> m_back;

  public:
    explicit in_flight_list(const device_context * ld)
      : m_front(std::make_unique<in_flight>(ld->unified_queue_family()))
      , m_back(std::make_unique<in_flight>(ld->unified_queue_family())) {
    }

    [[nodiscard]] in_flight * flip() noexcept {
      std::swap(m_front, m_back);
      return m_back.get();
    }
  };
}
