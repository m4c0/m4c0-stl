#pragma once

#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/begin_one_time_submit.hpp"
#include "m4c0/vulkan/begin_render_pass_continue.hpp"
#include "m4c0/vulkan/command_buffer_guard.hpp"
#include "m4c0/vulkan/command_pool.hpp"
#include "m4c0/vulkan/end_command_buffer.hpp"

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
    [[nodiscard]] auto at(unsigned idx) const noexcept {
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

    [[nodiscard]] command_buffer_guard begin(unsigned index) const {
      auto cb = parent_t::at(index);
      cmd::begin_one_time_submit(cb).now();
      return command_buffer_guard { cb };
    }
  };

  template<unsigned Size>
  class secondary_command_buffer_list : public command_buffer_list<Size> {
    using parent_t = command_buffer_list<Size>;

  public:
    explicit secondary_command_buffer_list(int queue_family) : parent_t(queue_family) {
      parent_t::allocate().as_secondary_into(parent_t::buffers());
    }

    [[nodiscard]] command_buffer_guard begin(unsigned index, const render_pass * rp) const {
      auto cb = parent_t::at(index);
      cmd::begin_render_pass_continue(cb).with_render_pass(rp).now();
      return command_buffer_guard { cb };
    }

    [[nodiscard]] command_buffer_guard begin(unsigned index, const framebuffer * fb, const render_pass * rp) const {
      auto cb = parent_t::at(index);
      cmd::begin_render_pass_continue(cb).with_framebuffer(fb).with_render_pass(rp).now();
      return command_buffer_guard { cb };
    }
  };
}
