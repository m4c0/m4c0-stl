#include "m4c0/vulkan/surface.win32.hpp"

#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/surface.hpp"

#include <windows.h>

using namespace m4c0::vulkan;

surface surface::for_native_ptr(const native_provider * np) {
  VkWin32SurfaceCreateInfoKHR ci {};
  ci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  ci.hinstance = np->hinstance();
  ci.hwnd = np->hwnd();

  VkInstance i = loader::get_instance();
  return surface { details::safe_create<VkSurfaceKHR>(vkCreateWin32SurfaceKHR, i, &ci) };
}
