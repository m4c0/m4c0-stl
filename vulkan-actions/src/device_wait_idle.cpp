#include "m4c0/vulkan/device_wait_idle.hpp"
#include "m4c0/vulkan/loader.hpp"

void m4c0::vulkan::actions::device_wait_idle() {
  vkDeviceWaitIdle(loader::get_device());
}
