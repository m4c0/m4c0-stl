#pragma once

#include "m4c0/vulkan/base_command.hpp"

#include <vector>

namespace m4c0::vulkan::cmd {
  class execute_commands : base_command {
    std::vector<VkCommandBuffer> m_cmds {};

  public:
    explicit execute_commands(VkCommandBuffer cb) : base_command(cb) {
    }
    explicit execute_commands(const base_command & o) : base_command(o) {
    }

    [[nodiscard]] execute_commands & add_command_buffer(VkCommandBuffer cb) {
      m_cmds.push_back(cb);
      return *this;
    }

    void now() const;
  };
}
