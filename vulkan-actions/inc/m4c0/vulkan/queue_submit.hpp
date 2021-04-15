#pragma once

using VkCommandBuffer = struct VkCommandBuffer_T *;

namespace m4c0::vulkan {
  class fence;
  class queue;
  class semaphore;
}

namespace m4c0::vulkan::actions {
  class queue_submit {
    VkCommandBuffer m_cmd_buf;
    const queue * m_queue;
    const semaphore * m_wait_semaphore;
    const semaphore * m_signal_semaphore;
    const fence * m_fence;

  public:
    [[nodiscard]] constexpr queue_submit & with_command_buffer(VkCommandBuffer c) noexcept {
      m_cmd_buf = c;
      return *this;
    }
    [[nodiscard]] constexpr queue_submit & with_queue(const queue * q) noexcept {
      m_queue = q;
      return *this;
    }
    [[nodiscard]] constexpr queue_submit & with_fence(const fence * f) noexcept {
      m_fence = f;
      return *this;
    }
    [[nodiscard]] constexpr queue_submit & with_signal_semaphore(const semaphore * s) noexcept {
      m_signal_semaphore = s;
      return *this;
    }
    [[nodiscard]] constexpr queue_submit & with_wait_semaphore(const semaphore * s) noexcept {
      m_wait_semaphore = s;
      return *this;
    }
    void now() const;
  };
}
