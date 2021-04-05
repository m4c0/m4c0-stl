#include "m4c0/vulkan/loader.hpp"

void m4c0::vulkan::loader::initialise() {
}

static VkInstance & global_instance() {
  static VkInstance i {};
  return i;
}
void m4c0::vulkan::loader::load_instance(VkInstance i) {
  global_instance() = i;
}
VkInstance m4c0::vulkan::loader::get_instance() {
  return global_instance();
}

static VkDevice & global_device() {
  static VkDevice d {};
  return d;
}
void m4c0::vulkan::loader::load_device(VkDevice d) {
  global_device() = d;
}
VkDevice m4c0::vulkan::loader::get_device() {
  return global_device();
}
