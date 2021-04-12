#include "check.hpp"
#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/copy_buffer_to_image.hpp"
#include "m4c0/vulkan/image.hpp"

void m4c0::vulkan::cmd::copy_buffer_to_image::now() const {
  VkBufferImageCopy r {};
  r.bufferOffset = m_source_offset;
  r.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  r.imageSubresource.layerCount = 1;
  r.imageExtent.width = m_target_width;
  r.imageExtent.height = m_target_height;
  r.imageExtent.depth = 1;
  vkCmdCopyBufferToImage(
      pointer(),
      m_source->pointer(),
      m_target->pointer(),
      VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      1,
      &r);
}
