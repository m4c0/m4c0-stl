#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/shader_module.hpp"

using namespace m4c0::vulkan;

shader_module shader_module::create_from_spv(std::span<const std::uint32_t> spv) {
  VkShaderModuleCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  info.pCode = spv.data();
  info.codeSize = spv.size();
  return shader_module { details::safe_create_d<VkShaderModule>(vkCreateShaderModule, &info) };
}

template<>
void details::handle<VkShaderModule>::reset() {
  vkDestroyShaderModule(loader::get_device(), pointer(), nullptr);
}
