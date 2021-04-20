#pragma once

#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/command_pool.hpp"

#include <array>

namespace m4c0::vulkan::tools {
  template<unsigned Size>
  class command_buffer_list {
    command_pool m_pool;
    std::array<VkCommandBuffer, Size> m_buffers {};

  protected:
    [[nodiscard]] auto allocate() const {
      return actions::allocate_command_buffers().with_command_pool(&m_pool);
    }
    [[nodiscard]] constexpr auto & buffers() {
      return m_buffers;
    }

    explicit command_buffer_list(int queue_family)
      : m_pool(command_pool::create_resettable_for_queue_family(queue_family)) {
    }

  public:
    [[nodiscard]] auto operator[](unsigned idx) const noexcept {
      return m_buffers[idx];
    }
  };
  template<unsigned Size>
  class primary_command_buffer_list : public command_buffer_list<Size> {
    using parent_t = command_buffer_list<Size>;

  public:
    explicit primary_command_buffer_list(int queue_family) : parent_t(queue_family) {
      parent_t::allocate().as_primary_into(parent_t::buffers());
    }
  };

  template<unsigned Size>
  class secondary_command_buffer_list : public command_buffer_list<Size> {
    using parent_t = command_buffer_list<Size>;

  public:
    explicit secondary_command_buffer_list(int queue_family) : parent_t(queue_family) {
      parent_t::allocate().as_secondary_into(parent_t::buffers());
    }
  };
}
