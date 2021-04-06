#include "m4c0/vulkan/debug_utils_messenger.hpp"
#include "m4c0/vulkan/device.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/queue.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "m4c0/vulkan/surface_format.hpp"

using namespace m4c0::vulkan::details;
using namespace m4c0::vulkan;

int main() {
  auto i = instance::create_for_app("dummy app");
  auto dbg = debug_utils_messenger::create();
  auto s = surface::for_native_ptr(nullptr);
  auto pd = physical_device::best_for(&s);
  auto d = device::create_for_physical_device(&pd);

  VkQueue q = queue::get_for_family(pd.unified_queue_family()).pointer();

  auto sfmt = surface_format::best_from_device_and_surface(&pd, &s);
  auto rp = render_pass::create_with_opiniated_defaults_and_format(&sfmt);

  d.wait_idle();
}
