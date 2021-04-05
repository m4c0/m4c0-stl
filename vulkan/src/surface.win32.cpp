#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "safe_calls.hpp"

#include <windows.h>

using namespace m4c0::vulkan;

surface surface::for_native_ptr(native_ptr_t native) {
  VkWin32SurfaceCreateInfoKHR ci {};
  ci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  ci.hinstance = GetModuleHandle(NULL);
  ci.hwnd = static_cast<HWND>(native);

  VkInstance i = loader::get_instance();
  return surface { details::safe_create<VkSurfaceKHR>(vkCreateWin32SurfaceKHR, i, &ci) };
}
