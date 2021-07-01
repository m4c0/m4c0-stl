#pragma once

#include "m4c0/vulkan/base_command.hpp"
#include "m4c0/vulkan/host_staged_image_buffer.hpp"
#include "m4c0/vulkan/local_image.hpp"

#include <memory>

namespace m4c0::vulkan::tools {
  class staged_image {
    enum class state { loaded, copying, copied, clear };

    std::unique_ptr<host_staged_image_buffer> m_stage;
    local_image m_image {};
    state m_state { state::loaded };

    void copy(VkCommandBuffer cb);

  public:
    staged_image(
        const m4c0::vulkan::tools::logical_device * ld,
        const m4c0::native_handles * nptr,
        const char * t_name,
        const char * t_ext);

    void build_primary_command_buffer(VkCommandBuffer cb);

    [[nodiscard]] constexpr auto image_view() const noexcept {
      return m_image.image_view();
    }
  };
}
