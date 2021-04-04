#include "m4c0/vulkan/surface.hpp"
#include "volk.hpp"

using namespace m4c0::vulkan;

template<>
void details::handle<VkSurfaceKHR>::reset() {
  vkDestroySurfaceKHR(volkGetLoadedInstance(), pointer(), nullptr);
}
