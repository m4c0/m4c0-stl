#include "m4c0/vulkan/loader.hpp"

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
