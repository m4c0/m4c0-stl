#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/queue.hpp"

using namespace m4c0::vulkan;

queue queue::get_for_family(int qf) {
  VkQueue q {};
  vkGetDeviceQueue(loader::get_device(), qf, 0, &q);
  return queue { q };
}
