#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"
#include "safe_calls.hpp"

using namespace m4c0::vulkan;

static auto create_info_for_extent(unsigned int w, unsigned int h) {
  VkImageCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  info.imageType = VK_IMAGE_TYPE_2D;
  info.extent = { w, h, 1 };
  info.mipLevels = 1;
  info.arrayLayers = 1;
  info.tiling = VK_IMAGE_TILING_OPTIMAL;
  info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  info.samples = VK_SAMPLE_COUNT_1_BIT;
  return info;
}

image image::create_depth_with_extent(unsigned int w, unsigned int h) {
  auto info = create_info_for_extent(w, h);
  info.format = VK_FORMAT_D32_SFLOAT;
  info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
  return image { details::safe_create_d<VkImage>(vkCreateImage, &info) };
}
image image::create_rgba_with_extent(unsigned int w, unsigned int h) {
  auto info = create_info_for_extent(w, h);
  info.format = VK_FORMAT_R8G8B8A8_SRGB;
  info.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
  return image { details::safe_create_d<VkImage>(vkCreateImage, &info) };
}

template<>
void details::handle<VkImage>::reset() {
  vkDestroyImage(loader::get_device(), pointer(), nullptr);
}

memory_requirements image::memory_requirements() const {
  VkMemoryRequirements res {};
  vkGetImageMemoryRequirements(m4c0::vulkan::loader::get_device(), pointer(), &res);
  return vulkan::memory_requirements { res };
}
