#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/surface.hpp"

using namespace m4c0::vulkan;

template<>
void details::handle<VkSurfaceKHR>::reset() {
  vkDestroySurfaceKHR(loader::get_instance(), pointer(), nullptr);
}
