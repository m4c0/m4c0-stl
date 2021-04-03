#include "m4c0/vulkan/surface.hpp"

#include <volk.h>

using namespace m4c0::vulkan;

template<>
void details::handle<VkSurfaceKHR>::reset() {
  vkDestroySurfaceKHR(volkGetLoadedInstance(), pointer(), nullptr);
}
