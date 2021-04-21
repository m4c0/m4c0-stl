#pragma once

#include "m4c0/vulkan/base_render_pass_command.hpp"

namespace m4c0::vulkan::cmd {
  struct begin_render_pass_continue : public base_render_pass_command<begin_render_pass_continue> {
    using base_render_pass_command::base_render_pass_command;

    void now() const;
  };
}
