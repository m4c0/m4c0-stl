#include "m4c0/vulkan/command_buffer_list.hpp"
#include "m4c0/vulkan/logical_device.hpp"

int main() {
  m4c0::vulkan::tools::logical_device d { "test-app", nullptr };

  m4c0::vulkan::tools::primary_command_buffer_list<3> pcb { d.unified_queue_family() };
  m4c0::vulkan::tools::secondary_command_buffer_list<3> scb { d.unified_queue_family() };
}
