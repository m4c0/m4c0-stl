#pragma once

#include "m4c0/vulkan/base_command.hpp"

using VkDescriptorSet = struct VkDescriptorSet_T *;

namespace m4c0::vulkan {
  class pipeline_layout;
}

namespace m4c0::vulkan::cmd {
  class bind_descriptor_set : base_command {
    const pipeline_layout * m_pipeline_layout;
    VkDescriptorSet m_descriptor_set;
    unsigned m_first_set {};

  public:
    using base_command::base_command;

    [[nodiscard]] constexpr bind_descriptor_set & with_descriptor_set(VkDescriptorSet p) noexcept {
      m_descriptor_set = p;
      return *this;
    }
    [[nodiscard]] constexpr bind_descriptor_set & with_pipeline_layout(const pipeline_layout * p) noexcept {
      m_pipeline_layout = p;
      return *this;
    }
    [[nodiscard]] constexpr bind_descriptor_set & with_first_set(unsigned i) noexcept {
      m_first_set = i;
      return *this;
    }

    void now() const;
  };
}
