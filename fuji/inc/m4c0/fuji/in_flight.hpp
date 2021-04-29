#pragma once

#include "m4c0/fuji/semaphores.hpp"
#include "m4c0/vulkan/command_buffer_list.hpp"
#include "m4c0/vulkan/fence.hpp"

namespace m4c0::fuji {
  class in_flight {
    image_available_semaphore m_ia_semaphore;
    render_finished_semaphore m_rf_semaphore;
    vulkan::fence m_fence;
    vulkan::tools::secondary_command_buffer_list<1> m_cmd_pool;

  public:
    explicit in_flight(int queue)
      : m_ia_semaphore { vulkan::semaphore::create() }
      , m_rf_semaphore { vulkan::semaphore::create() }
      , m_fence { vulkan::fence::create_signaled() }
      , m_cmd_pool { queue } {
    }

    [[nodiscard]] constexpr auto * image_available_semaphore() const noexcept {
      return &m_ia_semaphore;
    }
    [[nodiscard]] constexpr auto * render_finished_semaphore() const noexcept {
      return &m_rf_semaphore;
    }
    [[nodiscard]] constexpr auto * fence() const noexcept {
      return &m_fence;
    }
    void wait_for_fence() const {
      m_fence.wait_and_reset();
    }

    [[nodiscard]] auto begin_secondary_command_buffer(const vulkan::render_pass * rp) const noexcept {
      return m_cmd_pool.begin(0, rp);
    }
  };
}
