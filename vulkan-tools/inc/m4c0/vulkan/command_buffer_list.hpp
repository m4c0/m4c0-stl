#pragma once

#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/begin_one_time_submit.hpp"
#include "m4c0/vulkan/begin_render_pass_continue.hpp"
#include "m4c0/vulkan/command_pool.hpp"
#include "m4c0/vulkan/end_command_buffer.hpp"

#include <array>

namespace m4c0::vulkan::tools {
  class command_buffer_guard {
    VkCommandBuffer m_cmd_buf;

  public:
    explicit constexpr command_buffer_guard(VkCommandBuffer cb) : m_cmd_buf(cb) {
    }
    ~command_buffer_guard() {
      cmd::end_command_buffer(m_cmd_buf).now();
    }

    command_buffer_guard(command_buffer_guard &&) = delete;
    command_buffer_guard(const command_buffer_guard &) = delete;
    command_buffer_guard & operator=(command_buffer_guard &&) = delete;
    command_buffer_guard & operator=(const command_buffer_guard &) = delete;

    [[nodiscard]] constexpr VkCommandBuffer command_buffer() const noexcept {
      return m_cmd_buf;
    }
  };

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

    [[nodiscard]] command_buffer_guard begin(unsigned index, const framebuffer * fb, const render_pass * rp) const {
      auto cb = parent_t::at(index);
      cmd::begin_render_pass_continue(cb).with_framebuffer(fb).with_render_pass(rp).now();
      return command_buffer_guard { cb };
    }
  };
}
