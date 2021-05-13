#include "m4c0/native_handles.metal.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/surface.hpp"

using namespace m4c0::vulkan;

surface surface::for_native_ptr(const native_handles * np) {
  VkMetalSurfaceCreateInfoEXT ci {};
  ci.sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT;
  ci.pLayer = np->layer();

  VkInstance i = loader::get_instance();
  return surface { details::safe_create<VkSurfaceKHR>(vkCreateMetalSurfaceEXT, i, &ci) };
}
