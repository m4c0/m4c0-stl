#include "m4c0/vulkan/surface.android.hpp"

#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/surface.hpp"

using namespace m4c0::vulkan;

surface surface::for_native_ptr(const native_provider * np) {
  VkAndroidSurfaceCreateInfoKHR info {};
  info.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
  info.window = np->window();

  VkInstance i = loader::get_instance();
  return surface { details::safe_create<VkSurfaceKHR>(vkCreateAndroidSurfaceKHR, i, &info) };
}
