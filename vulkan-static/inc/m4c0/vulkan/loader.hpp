#pragma once

#include <vulkan/vulkan.h>

namespace m4c0::vulkan::loader {
  void load_instance(VkInstance i);
  VkInstance get_instance();
}
