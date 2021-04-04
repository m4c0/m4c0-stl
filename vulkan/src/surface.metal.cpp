#include "m4c0/vulkan/surface.hpp"
#include "safe_calls.hpp"
#include "volk.hpp"

using namespace m4c0::vulkan;

surface surface::for_native_ptr(native_ptr_t native) {
  VkMetalSurfaceCreateInfoEXT ci {};
  ci.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
  ci.pLayer = static_cast<CAMetalLayer *>(native);

  VkInstance i = volk::get_instance();
  return surface { details::safe_create<VkSurfaceKHR>(vkCreateMetalSurfaceEXT, i, &ci) };
}
