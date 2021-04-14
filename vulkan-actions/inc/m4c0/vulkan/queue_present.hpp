#pragma once

namespace m4c0::vulkan {
  class semaphore;
  class swapchain;
  class queue;
}
namespace m4c0::vulkan::actions {
  class queue_present {
    const semaphore * m_semaphore;
    const swapchain * m_swapchain;
    const queue * m_present_queue;
    unsigned m_image_index;

  public:
    [[nodiscard]] constexpr queue_present & with_wait_semaphore(const semaphore * s) noexcept {
      m_semaphore = s;
      return *this;
    }
    [[nodiscard]] constexpr queue_present & with_swapchain(const swapchain * s) noexcept {
      m_swapchain = s;
      return *this;
    }
    [[nodiscard]] constexpr queue_present & with_present_queue(const queue * q) noexcept {
      m_present_queue = q;
      return *this;
    }
    [[nodiscard]] constexpr queue_present & with_image_index(unsigned i) noexcept {
      m_image_index = i;
      return *this;
    }
    void now() const;
  };

}
