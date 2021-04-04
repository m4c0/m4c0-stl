#include "volk.hpp"

void m4c0::vulkan::volk::load_instance(VkInstance i) {
  static struct initer {
    initer() {
      volkInitialize();
    }
  } init;

  volkLoadInstance(i);
}
VkInstance m4c0::vulkan::volk::get_instance() {
  return volkGetLoadedInstance();
}
