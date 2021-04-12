#include "check.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/pipeline_barrier.hpp"

static constexpr VkImageMemoryBarrier create_memory_barrier(VkImage img) {
  VkImageMemoryBarrier imb {};
  imb.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  imb.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  imb.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  imb.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  imb.subresourceRange.levelCount = 1;
  imb.subresourceRange.layerCount = 1;
  imb.image = img;
  return imb;
}

void m4c0::vulkan::cmd::image_memory_pipeline_barrier::from_host_to_transfer() const {
  auto imb = create_memory_barrier(m_image->pointer());
  imb.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imb.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  imb.srcAccessMask = 0;
  imb.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

  constexpr const auto src_flags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
  constexpr const auto dst_flags = VK_PIPELINE_STAGE_TRANSFER_BIT;
  vkCmdPipelineBarrier(pointer(), src_flags, dst_flags, 0, 0, nullptr, 0, nullptr, 1, &imb);
}
void m4c0::vulkan::cmd::image_memory_pipeline_barrier::from_transfer_to_fragment_shader() const {
  auto imb = create_memory_barrier(m_image->pointer());
  imb.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  imb.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
  imb.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
  imb.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

  constexpr const auto src_flags = VK_PIPELINE_STAGE_TRANSFER_BIT;
  constexpr const auto dst_flags = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  vkCmdPipelineBarrier(pointer(), src_flags, dst_flags, 0, 0, nullptr, 0, nullptr, 1, &imb);
}
