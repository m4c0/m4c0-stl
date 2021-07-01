#include "m4c0/vulkan/copy_buffer_to_image.hpp"
#include "m4c0/vulkan/pipeline_barrier.hpp"
#include "m4c0/vulkan/staged_image.hpp"

using namespace m4c0::vulkan::tools;

[[nodiscard]] static auto create_stage(
    const m4c0::vulkan::tools::logical_device * ld,
    const m4c0::native_handles * nptr,
    const char * t_name,
    const char * t_ext) {
  auto asset = m4c0::assets::typed_stb_image<>::load_from_asset(nptr, t_name, t_ext);
  return std::make_unique<m4c0::vulkan::tools::host_staged_image_buffer>(ld, asset);
}

staged_image::staged_image(
    const m4c0::vulkan::tools::logical_device * ld,
    const m4c0::native_handles * nptr,
    const char * t_name,
    const char * t_ext)
  : m_stage(create_stage(ld, nptr, t_name, t_ext))
  , m_image(ld, m_stage->width(), m_stage->height()) {
}

void staged_image::build_primary_command_buffer(VkCommandBuffer cb) {
  switch (m_state) {
  case state::loaded:
    copy(cb);
    m_state = state::copying;
    break;
  case state::copying:
    m_state = state::copied;
    break;
  case state::copied:
    m_stage.reset();
    m_state = state::clear;
    break;
  case state::clear:
    break;
  }
}

void staged_image::copy(VkCommandBuffer cb) {
  const auto * dst = m_image.image();
  auto barrier = m4c0::vulkan::cmd::image_memory_pipeline_barrier(cb).with_image(dst);

  barrier.from_host_to_transfer();
  m4c0::vulkan::cmd::copy_buffer_to_image(cb)
      .with_source_buffer(m_stage->buffer())
      .with_target_extent(m_stage->width(), m_stage->height())
      .with_target_image(dst)
      .now();
  barrier.from_transfer_to_fragment_shader();
}
