#include "m4c0/fuji/depth_buffer.hpp"
#include "m4c0/fuji/device_context.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"

using namespace m4c0::fuji;

depth_buffer::depth_buffer(const device_context * ld, vulkan::extent_2d re)
  : m_image { vulkan::image::create_depth_with_extent(re) }
  , m_memory { ld->create_local_memory(&m_image) }
  , m_bind { &m_image, &m_memory }
  , m_image_view { vulkan::image_view::create_depth_for_image(&m_image) } {};
