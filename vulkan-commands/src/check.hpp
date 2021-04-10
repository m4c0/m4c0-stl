#pragma once

#include "m4c0/log.hpp"
#include "m4c0/vulkan/loader.hpp"

namespace m4c0::vulkan::cmd {
  // TODO: add this when clang supports it
  // const std::source_location & location = std::source_location::current()
  static void check(VkResult res) {
    if (res == VK_SUCCESS) return;
    m4c0::log::warning("Something went wrong");
  }
}
