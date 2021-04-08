#include "m4c0/vulkan/command_pool.hpp"
#include "m4c0/vulkan/debug_utils_messenger.hpp"
#include "m4c0/vulkan/descriptor_pool.hpp"
#include "m4c0/vulkan/descriptor_set_layout.hpp"
#include "m4c0/vulkan/device.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/memory_requirements.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/pipeline.hpp"
#include "m4c0/vulkan/pipeline_layout.hpp"
#include "m4c0/vulkan/queue.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/shader_module.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "m4c0/vulkan/surface_format.hpp"

using namespace m4c0::vulkan;

int main() {
  auto i = instance::create_for_app("dummy app");
  auto dbg = debug_utils_messenger::create();
  auto s = surface::for_native_ptr(nullptr);
  auto pd = physical_device::best_for(&s);
  auto d = device::create_for_physical_device(&pd);

  VkQueue q = queue::get_for_family(pd.unified_queue_family()).pointer();

  auto sfmt = surface_format::best_from_device_and_surface(&pd, &s);
  auto rp = render_pass::create_with_opiniated_defaults_and_format(&sfmt);

  command_pool::create_resettable_for_queue_family(pd.unified_queue_family()).allocate(3, true);

  auto mr = image::create_depth_with_extent(3, 2).memory_requirements();

  framebuffer fb = framebuffer::builder().with_extent(3, 2).build();
  descriptor_pool pool = descriptor_pool::builder().add_combined_image_sampler_type(1).build();

  descriptor_set_layout dsl = descriptor_set_layout::builder().add_fragment_sampler_binding().build();
  pipeline_layout pl = pipeline_layout::builder()
                           .add_descriptor_set_layout(&dsl)
                           .add_vertex_push_constant_with_size_and_offset(4, 0)
                           .build();

  auto spv = std::array<std::uint32_t, 4> { 1, 2, 3, 4 };
  shader_module sm = shader_module::create_from_spv(spv);

  pipeline p = pipeline::builder()
                   .with_pipeline_layout(&pl)
                   .with_render_pass(&rp)
                   .add_vertex_stage(sm, "vmain")
                   .add_fragment_stage(sm, "fmain")
                   .add_vertex_binding_with_stride(4)
                   .add_vertex_binding_instanced_with_stride(4)
                   .add_vec4_attribute_with_bind_and_offset(0, 0)
                   .add_vec2_attribute_with_bind_and_offset(1, 0)
                   .add_vec2_attribute_with_bind_and_offset(1, 2)
                   .build();

  d.wait_idle();
}
