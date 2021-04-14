#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/image_view.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/surface_format.hpp"

using namespace m4c0::vulkan;

static auto create_info_for_aspect_mask(VkImageAspectFlags aspect_mask) {
  VkImageViewCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  info.subresourceRange.layerCount = 1;
  info.subresourceRange.levelCount = 1;
  info.subresourceRange.aspectMask = aspect_mask;
  return info;
}

image_view image_view::create_depth_for_image(const image * img) {
  auto info = create_info_for_aspect_mask(VK_IMAGE_ASPECT_DEPTH_BIT);
  info.image = img->pointer();
  info.format = VK_FORMAT_D32_SFLOAT;
  return image_view { details::safe_create_d<VkImageView>(vkCreateImageView, &info) };
}
image_view image_view::create_rgba_for_image(const image * img) {
  auto info = create_info_for_aspect_mask(VK_IMAGE_ASPECT_COLOR_BIT);
  info.image = img->pointer();
  info.format = VK_FORMAT_R8G8B8A8_SRGB;
  return image_view { details::safe_create_d<VkImageView>(vkCreateImageView, &info) };
}
image_view image_view::create_rgba_for_image_and_format(VkImage img, const surface_format * sfmt) {
  auto info = create_info_for_aspect_mask(VK_IMAGE_ASPECT_COLOR_BIT);
  info.image = img;
  info.format = sfmt->pointer()->format;
  return image_view { details::safe_create_d<VkImageView>(vkCreateImageView, &info) };
}

template<>
void details::handle<VkImageView>::reset() {
  safe_destroy_d(vkDestroyImageView, this);
}
