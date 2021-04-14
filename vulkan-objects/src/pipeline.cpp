#include "m4c0/vulkan/handle.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/pipeline.hpp"
#include "m4c0/vulkan/pipeline_layout.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/shader_module.hpp"

#include <array>
#include <vector>

using namespace m4c0::vulkan;

struct pipeline::builder::attributes : std::vector<VkVertexInputAttributeDescription> {};
struct pipeline::builder::bindings : std::vector<VkVertexInputBindingDescription> {};
struct pipeline::builder::shaders : std::vector<VkPipelineShaderStageCreateInfo> {};

template<>
void details::handle<VkPipeline>::reset() {
  safe_destroy_d(vkDestroyPipeline, this);
}

pipeline::builder::builder() {
  m_attributes.make_new();
  m_bindings.make_new();
  m_shaders.make_new();
}
pipeline pipeline::builder::build() {
  VkPipelineInputAssemblyStateCreateInfo input_assembly {};
  input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  VkPipelineColorBlendAttachmentState color_blend_attachment {};
  color_blend_attachment.colorWriteMask = static_cast<unsigned>(VK_COLOR_COMPONENT_R_BIT) | VK_COLOR_COMPONENT_G_BIT
                                        | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

  VkPipelineColorBlendStateCreateInfo color_blend {};
  color_blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blend.logicOp = VK_LOGIC_OP_COPY;
  color_blend.attachmentCount = 1;
  color_blend.pAttachments = &color_blend_attachment;

  VkPipelineDepthStencilStateCreateInfo depth_stencil {};
  depth_stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depth_stencil.depthTestEnable = VK_TRUE;
  depth_stencil.depthWriteEnable = VK_TRUE;
  depth_stencil.depthCompareOp = VK_COMPARE_OP_LESS;

  std::array<VkDynamicState, 2> states { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };

  VkPipelineDynamicStateCreateInfo dynamic_state {};
  dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state.pDynamicStates = states.data();
  dynamic_state.dynamicStateCount = states.size();

  VkPipelineMultisampleStateCreateInfo multisample {};
  multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

  VkPipelineRasterizationStateCreateInfo raster {};
  raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  raster.polygonMode = VK_POLYGON_MODE_FILL;
  raster.lineWidth = 1;
  raster.cullMode = VK_CULL_MODE_BACK_BIT;
  raster.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

  VkPipelineViewportStateCreateInfo viewport {};
  viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport.scissorCount = 1;
  viewport.viewportCount = 1;

  VkPipelineVertexInputStateCreateInfo vertex_input {};
  vertex_input.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input.vertexAttributeDescriptionCount = m_attributes->size();
  vertex_input.pVertexAttributeDescriptions = m_attributes->data();
  vertex_input.vertexBindingDescriptionCount = m_bindings->size();
  vertex_input.pVertexBindingDescriptions = m_bindings->data();

  VkGraphicsPipelineCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  info.basePipelineIndex = -1;
  info.layout = m_layout->pointer();
  info.renderPass = m_render_pass->pointer();
  info.stageCount = m_shaders->size();
  info.pStages = m_shaders->data();
  info.pInputAssemblyState = &input_assembly;
  info.pColorBlendState = &color_blend;
  info.pDepthStencilState = &depth_stencil;
  info.pDynamicState = &dynamic_state;
  info.pMultisampleState = &multisample;
  info.pRasterizationState = &raster;
  info.pVertexInputState = &vertex_input;
  info.pViewportState = &viewport;

  return pipeline { details::safe_create_d<VkPipeline>(vkCreateGraphicsPipelines, nullptr, 1, &info) };
}

pipeline::builder & pipeline::builder::add_fragment_stage(const shader_module & sm, const char * name) {
  VkPipelineShaderStageCreateInfo ci {};
  ci.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  ci.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  ci.module = sm.pointer();
  ci.pName = name;
  m_shaders->push_back(ci);
  return *this;
}
pipeline::builder & pipeline::builder::add_vertex_stage(const shader_module & sm, const char * name) {
  VkPipelineShaderStageCreateInfo ci {};
  ci.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  ci.stage = VK_SHADER_STAGE_VERTEX_BIT;
  ci.module = sm.pointer();
  ci.pName = name;
  m_shaders->push_back(ci);
  return *this;
}

pipeline::builder & pipeline::builder::add_vertex_binding_with_stride(unsigned int stride) {
  VkVertexInputBindingDescription vibd {};
  vibd.binding = m_bindings->size();
  vibd.stride = stride;
  vibd.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  m_bindings->push_back(vibd);
  return *this;
}
pipeline::builder & pipeline::builder::add_vertex_binding_instanced_with_stride(unsigned int stride) {
  VkVertexInputBindingDescription vibd {};
  vibd.binding = m_bindings->size();
  vibd.stride = stride;
  vibd.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
  m_bindings->push_back(vibd);
  return *this;
}

pipeline::builder & pipeline::builder::add_vec2_attribute_with_bind_and_offset(
    unsigned int binding,
    unsigned int offset) {
  VkVertexInputAttributeDescription viad {};
  viad.binding = binding;
  viad.location = m_attributes->size();
  viad.offset = offset;
  viad.format = VK_FORMAT_R32G32_SFLOAT;
  m_attributes->push_back(viad);
  return *this;
}
pipeline::builder & pipeline::builder::add_vec3_attribute_with_bind_and_offset(
    unsigned int binding,
    unsigned int offset) {
  VkVertexInputAttributeDescription viad {};
  viad.binding = binding;
  viad.location = m_attributes->size();
  viad.offset = offset;
  viad.format = VK_FORMAT_R32G32B32_SFLOAT;
  m_attributes->push_back(viad);
  return *this;
}
pipeline::builder & pipeline::builder::add_vec4_attribute_with_bind_and_offset(
    unsigned int binding,
    unsigned int offset) {
  VkVertexInputAttributeDescription viad {};
  viad.binding = binding;
  viad.location = m_attributes->size();
  viad.offset = offset;
  viad.format = VK_FORMAT_R32G32B32A32_SFLOAT;
  m_attributes->push_back(viad);
  return *this;
}
