#pragma once

#include "m4c0/vulkan/base_command.hpp"

namespace m4c0::vulkan::cmd {
  struct begin_one_time_submit : base_command {
    using base_command::base_command;
    explicit constexpr begin_one_time_submit(const base_command & o) : base_command(o) {
    }
    void now() const;
  };
}
