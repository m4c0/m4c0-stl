#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/buffer_memory_bind.hpp"
#include "m4c0/vulkan/command_buffer_list.hpp"
#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/image_memory_bind.hpp"
#include "m4c0/vulkan/logical_device.hpp"
#include "m4c0/vulkan/queue_submit.hpp"
#include "m4c0/vulkan/typed_semaphore.hpp"

struct my_semaphore : public m4c0::vulkan::tools::typed_semaphore<my_semaphore> {};
struct other_semaphore : public m4c0::vulkan::tools::typed_semaphore<other_semaphore> {};

void use_my_semaphore(const my_semaphore * signal, const other_semaphore * wait) {
  m4c0::vulkan::actions::queue_submit().with_signal_semaphore(signal).with_wait_semaphore(wait).now();
}

class bound_image {
  m4c0::vulkan::image img { /* ... */ };
  m4c0::vulkan::device_memory mem { /* ... */ };
  m4c0::vulkan::tools::image_memory_bind bind { &img, &mem };
};
class bound_buffer {
  m4c0::vulkan::buffer buf { /* ... */ };
  m4c0::vulkan::device_memory mem { /* ... */ };
  m4c0::vulkan::tools::buffer_memory_bind bind { &buf, &mem };
};

int main() {
  m4c0::vulkan::tools::logical_device d { "test-app", nullptr };

  m4c0::vulkan::tools::primary_command_buffer_list<3> pcb { d.unified_queue_family() };
  m4c0::vulkan::tools::secondary_command_buffer_list<3> scb { d.unified_queue_family() };

  {
    auto pg = pcb.begin(0);
    // I feel like there should be some compiler-enforced way of setting the second only be achievable via the primary
    auto sg = scb.begin(0, nullptr, nullptr);
  }
}
