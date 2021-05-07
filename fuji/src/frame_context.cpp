#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/fuji/swapchain_context.hpp"
#include "m4c0/vulkan/image_view.hpp"
#include "m4c0/vulkan/surface_format.hpp"

using namespace m4c0::fuji;

static auto create_image_view(frame_context::image_t image, m4c0::vulkan::surface_format sfmt) {
  return m4c0::vulkan::image_view::create_rgba_for_image_and_format(image, &sfmt);
}

frame_context::frame_context(const device_context * ld, const swapchain_context * sc, image_t image)
  : m_image_view { create_image_view(image, ld->best_surface_format()) }
  , m_command_pool { ld->unified_queue_family() }
  , m_framebuffer { m4c0::vulkan::framebuffer::builder()
                        .with_extent(sc->render_extent())
                        .with_render_pass(ld->render_pass())
                        .add_attachment(&m_image_view)
                        .add_attachment(sc->depth_buffer()->image_view())
                        .build() } {
}
