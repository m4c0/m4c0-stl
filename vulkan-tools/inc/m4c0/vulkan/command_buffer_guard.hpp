#pragma once

#include "m4c0/vulkan/end_command_buffer.hpp"

namespace m4c0::vulkan::tools {
  struct command_buffer_guard : public cmd::base_command {
    using cmd::base_command::base_command;
    ~command_buffer_guard() {
      cmd::end_command_buffer(*this).now();
    }

    command_buffer_guard(command_buffer_guard &&) = delete;
    command_buffer_guard(const command_buffer_guard &) = delete;
    command_buffer_guard & operator=(command_buffer_guard &&) = delete;
    command_buffer_guard & operator=(const command_buffer_guard &) = delete;
  };
}
