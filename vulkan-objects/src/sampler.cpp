#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/sampler.hpp"

using namespace m4c0::vulkan;

sampler sampler::create_with_opiniated_defaults() {
  static constexpr const auto max_anisotropy_ever = 16.0;

  VkSamplerCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  info.magFilter = VK_FILTER_LINEAR;
  info.minFilter = VK_FILTER_LINEAR;
  info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  info.anisotropyEnable = VK_TRUE;
  info.maxAnisotropy = max_anisotropy_ever;
  info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  info.unnormalizedCoordinates = VK_FALSE; // [0, 1) v [0, w)
  info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  return sampler { details::safe_create_d<VkSampler>(vkCreateSampler, &info) };
}

template<>
void details::base_handle<VkSampler_T>::reset() {
  safe_destroy_d(vkDestroySampler, this);
}
