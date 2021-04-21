#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan {
  class image;
}
namespace m4c0::vulkan::cmd {
  class image_memory_pipeline_barrier : base_command {
    const image * m_image {};

  public:
    using base_command::base_command;
    explicit constexpr image_memory_pipeline_barrier(const base_command & o) : base_command(o) {
    }

    [[nodiscard]] image_memory_pipeline_barrier & with_image(const image * img) noexcept {
      m_image = img;
      return *this;
    }
    void from_host_to_transfer() const;
    void from_transfer_to_fragment_shader() const;
  };
}
