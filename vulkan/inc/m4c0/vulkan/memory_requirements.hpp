#pragma once

#include "m4c0/pimpl.hpp"

struct VkMemoryRequirements;

namespace m4c0::vulkan {
  class memory_requirements {
    m4c0::pimpl<VkMemoryRequirements> m_mr;

  public:
    explicit memory_requirements(VkMemoryRequirements mr);

    [[nodiscard]] constexpr const VkMemoryRequirements * pointer() const {
      return m_mr.get();
    }
  };
}
