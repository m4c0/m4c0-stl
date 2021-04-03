#include "m4c0/vulkan/handle.hpp"
#include "m4c0/vulkan/instance.hpp"

using namespace m4c0::vulkan::details;
using namespace m4c0::vulkan;

struct debug_utils_messenger : handle<struct VkDebugUtilsMessengerEXT_T *> {
  using handle::handle;
  [[nodiscard]] static debug_utils_messenger create();
};
struct surface : handle<struct VkSurfaceKHR_T *> {
  using handle::handle;
  [[nodiscard]] static surface for_native_ptr(void *);
};

int main() {
  auto i = instance::create_for_app("dummy app");
  auto dbg = debug_utils_messenger::create();
  auto s = surface::for_native_ptr(nullptr);
  // auto pd = physical_device::best_for(s);
  // auto d = device::best_for(pd);
}

#include <volk.h>

debug_utils_messenger debug_utils_messenger::create() {
  return debug_utils_messenger { nullptr };
}
template<>
void handle<VkDebugUtilsMessengerEXT>::reset() {
}

surface surface::for_native_ptr(void * native) {
  VkSurfaceKHR surf;
  return surface(surf);
}
template<>
void handle<VkSurfaceKHR>::reset() {
}
