#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "safe_calls.hpp"

#include <stdexcept>

using namespace m4c0::vulkan;

static unsigned find_memory_type_index(
    const physical_device * pd,
    unsigned int type_bits,
    VkMemoryAllocateFlags flags) {
  VkPhysicalDeviceMemoryProperties props {};
  vkGetPhysicalDeviceMemoryProperties(pd->pointer(), &props);

  for (std::uint32_t i = 0; i < props.memoryTypeCount; i++) {
    if ((type_bits & (1U << i)) == 0) {
      continue;
    }
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
    if ((static_cast<unsigned>(props.memoryTypes[i].propertyFlags) & flags) != flags) {
      continue;
    }
    return i;
  }

  throw std::runtime_error("Failed to find suitable memory type");
}

static VkDeviceMemory create(const physical_device * pd, const memory_requirements * mr, VkMemoryAllocateFlags flags) {
  VkMemoryAllocateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  info.allocationSize = mr->pointer()->size;
  info.memoryTypeIndex = find_memory_type_index(pd, mr->pointer()->memoryTypeBits, flags);
  return details::safe_create_d<VkDeviceMemory>(vkAllocateMemory, &info);
}

device_memory device_memory::create_host_memory(const physical_device * pd, const memory_requirements * mr) {
  return device_memory { create(pd, mr, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) };
}
device_memory device_memory::create_local_memory(const physical_device * pd, const memory_requirements * mr) {
  return device_memory { create(pd, mr, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) };
}

template<>
void details::handle<VkDeviceMemory>::reset() {
  vkFreeMemory(loader::get_device(), pointer(), nullptr);
}

device_memory::map_guard device_memory::map_all() {
  return map_with_offset_and_size(0, VK_WHOLE_SIZE);
}
device_memory::map_guard device_memory::map_from_beginning(std::uint64_t size) {
  return map_with_offset_and_size(0, size);
}
device_memory::map_guard device_memory::map_with_offset_and_size(std::uint64_t offset, std::uint64_t size) {
  return { pointer(), offset, size };
}

device_memory::map_guard::map_guard(VkDeviceMemory handle, std::uint64_t offset, std::uint64_t size)
  : m_handle(handle)
  , m_ptr() {
  details::safe_call(vkMapMemory, loader::get_device(), handle, offset, size, 0, &m_ptr);
}
device_memory::map_guard::~map_guard() {
  vkUnmapMemory(loader::get_device(), m_handle);
}
