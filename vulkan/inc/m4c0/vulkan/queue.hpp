#pragma once

using VkQueue = struct VkQueue_T *;

namespace m4c0::vulkan {
  class queue {
    VkQueue m_handle;

    explicit constexpr queue(VkQueue q) : m_handle(q) {
    }

  public:
    [[nodiscard]] static queue get_for_family(int qf);

    [[nodiscard]] constexpr VkQueue pointer() const {
      return m_handle;
    }
  };
}
