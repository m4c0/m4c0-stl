#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan::cmd {
  struct end_render_pass : base_command {
    using base_command::base_command;
    void now() const;
  };
}
