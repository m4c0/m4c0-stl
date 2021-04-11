#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan::cmd {
  struct command_buffer : base_command {
    explicit constexpr command_buffer(VkCommandBuffer cb) : base_command(cb) {
    }
    void end() const;
  };
}
