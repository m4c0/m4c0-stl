#pragma once

#include "m4c0/vulkan/command_buffer_list.hpp"
#include "m4c0/vulkan/execute_commands.hpp"
#include "m4c0/vulkan/extent_2d.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/image_view.hpp"
#include "m4c0/vulkan/render_pass_guard.hpp"

namespace m4c0::fuji {
  class device_context;
  class swapchain_context;

  class frame_context {
    vulkan::image_view m_image_view {};
    vulkan::tools::primary_command_buffer_list<1> m_command_pool;
    vulkan::framebuffer m_framebuffer;

  public:
    using image_t = vulkan::details::pointer_t<VkImage_T>;
    frame_context(const device_context * ld, const swapchain_context * sc, image_t image);

    template<typename Fn>
    [[nodiscard]] VkCommandBuffer build_primary_command_buffer(
        const vulkan::render_pass * rp,
        vulkan::extent_2d extent,
        VkCommandBuffer secondary,
        Fn && builder) const {
      auto guard = m_command_pool.begin(0);
      builder(guard.command_buffer());

      m4c0::vulkan::tools::render_pass_guard rpg { guard.command_buffer(), &m_framebuffer, rp, extent };
      m4c0::vulkan::cmd::execute_commands(guard.command_buffer()).add_command_buffer(secondary).now();

      return guard.command_buffer();
    }
  };
}
