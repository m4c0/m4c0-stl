#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"

using namespace m4c0::vulkan;

memory_requirements::memory_requirements(VkMemoryRequirements mr) {
  m_mr.make_new(mr);
}
