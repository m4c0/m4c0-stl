#pragma once

#include "m4c0/pimpl.hpp"
#include "m4c0/vulkan/handle.hpp"

struct VkPipeline_T;

namespace m4c0::vulkan {
  class pipeline_layout;
  class render_pass;
  class shader_module;

  class pipeline : public details::nd_handle<VkPipeline_T> {
  public:
    using nd_handle::nd_handle;

    class builder {
      const pipeline_layout * m_layout {};
      const render_pass * m_render_pass {};
      bool m_depth_enabled = true;

      class shaders;
      pimpl<shaders> m_shaders;

      class bindings;
      pimpl<bindings> m_bindings;

      class attributes;
      pimpl<attributes> m_attributes;

    public:
      builder();

      [[nodiscard]] constexpr builder & with_pipeline_layout(const pipeline_layout * pl) noexcept {
        m_layout = pl;
        return *this;
      }
      [[nodiscard]] constexpr builder & with_render_pass(const render_pass * rp) noexcept {
        m_render_pass = rp;
        return *this;
      }
      [[nodiscard]] constexpr builder & without_depth_test() noexcept {
        m_depth_enabled = false;
        return *this;
      }

      [[nodiscard]] builder & add_vertex_stage(const shader_module & sm, const char * name);
      [[nodiscard]] builder & add_fragment_stage(const shader_module & sm, const char * name);

      [[nodiscard]] builder & add_vertex_binding_with_stride(unsigned stride);
      [[nodiscard]] builder & add_vertex_binding_instanced_with_stride(unsigned stride);

      // Attributes must be 32bit aligned, normally. Then it makes more sense to avoid attribute types that won't align

      [[nodiscard]] builder & add_vec2_attribute_with_bind_and_offset(unsigned binding, unsigned offset);
      [[nodiscard]] builder & add_vec3_attribute_with_bind_and_offset(unsigned binding, unsigned offset);
      [[nodiscard]] builder & add_vec4_attribute_with_bind_and_offset(unsigned binding, unsigned offset);

      [[nodiscard]] builder & add_s8vec4_attribute_with_bind_and_offset(unsigned binding, unsigned offset);
      [[nodiscard]] builder & add_u8vec4_attribute_with_bind_and_offset(unsigned binding, unsigned offset);

      [[nodiscard]] builder & add_s16vec2_attribute_with_bind_and_offset(unsigned binding, unsigned offset);
      [[nodiscard]] builder & add_u16vec2_attribute_with_bind_and_offset(unsigned binding, unsigned offset);
      [[nodiscard]] builder & add_s16vec4_attribute_with_bind_and_offset(unsigned binding, unsigned offset);
      [[nodiscard]] builder & add_u16vec4_attribute_with_bind_and_offset(unsigned binding, unsigned offset);

      [[nodiscard]] pipeline build();
    };
  };
}
