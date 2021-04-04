#include "m4c0/vulkan/loader.hpp"

void m4c0::vulkan::loader::initialise() {
  volkInitialize();
}
void m4c0::vulkan::loader::load_instance(VkInstance i) {
  volkLoadInstance(i);
}
VkInstance m4c0::vulkan::loader::get_instance() {
  return volkGetLoadedInstance();
}
