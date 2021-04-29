#include "m4c0/fuji/device_context.hpp"
#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"

m4c0::vulkan::device_memory m4c0::fuji::device_context::create_local_memory(const m4c0::vulkan::image * img) const {
  auto mr = img->memory_requirements();
  return m4c0::vulkan::device_memory::create_local_memory(physical_device(), &mr);
}
m4c0::vulkan::device_memory m4c0::fuji::device_context::create_host_memory(const m4c0::vulkan::buffer * img) const {
  auto mr = img->memory_requirements();
  return m4c0::vulkan::device_memory::create_host_memory(physical_device(), &mr);
}
