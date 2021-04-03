#include "m4c0/vulkan/debug_utils_messenger.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/surface.hpp"

using namespace m4c0::vulkan::details;
using namespace m4c0::vulkan;

int main() {
  auto i = instance::create_for_app("dummy app");
  auto dbg = debug_utils_messenger::create();
  auto s = surface::for_native_ptr(nullptr);
  // auto pd = physical_device::best_for(s);
  // auto d = device::best_for(pd);
}
