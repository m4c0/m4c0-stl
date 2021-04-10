#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan::cmd {
  struct one_time_submit : base_command {
    explicit constexpr one_time_submit(VkCommandBuffer cb) : base_command(cb) {
    }
    void begin() const;
  };
}
