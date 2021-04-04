#pragma once

#include <volk.h>

namespace m4c0::vulkan::volk {
  void load_instance(VkInstance i);
  VkInstance get_instance();
}
