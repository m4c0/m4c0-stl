#pragma once

#include <vulkan/vulkan.h>

namespace m4c0::vulkan::loader {
  void initialise();

  void load_instance(VkInstance i);
  VkInstance get_instance();

  void load_device(VkDevice d);
  VkDevice get_device();
}
