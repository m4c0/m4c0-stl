#pragma once

#include "m4c0/vulkan/debug_utils_messenger.hpp"
#include "m4c0/vulkan/device.hpp"
#include "m4c0/vulkan/instance.hpp"
#include "m4c0/vulkan/physical_device.hpp"
#include "m4c0/vulkan/queue.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/surface.hpp"
#include "m4c0/vulkan/surface_capabilities.hpp"
#include "m4c0/vulkan/surface_format.hpp"
#include "m4c0/vulkan/swapchain.hpp"

namespace m4c0::vulkan::tools {
  class logical_device {
    instance m_instance;
    debug_utils_messenger m_debug;
    surface m_surface;
    physical_device m_physical_device;
    device m_device;
    queue m_unified_queue;

  public:
    logical_device(const char * app_name, const native_provider * np)
      : m_instance(instance::create_for_app(app_name))
      , m_debug(debug_utils_messenger::create())
      , m_surface(surface::for_native_ptr(np))
      , m_physical_device(physical_device::best_for(&m_surface))
      , m_device(device::create_for_physical_device(&m_physical_device))
      , m_unified_queue(queue::get_for_family(m_physical_device.unified_queue_family())) {
    }

    [[nodiscard]] render_pass best_render_pass() const {
      return render_pass::create_opiniated(&m_physical_device, &m_surface);
    }
    [[nodiscard]] surface_capabilities best_surface_capabilities() const {
      return surface_capabilities::for_physical_device_and_surface(&m_physical_device, &m_surface);
    }
    [[nodiscard]] surface_format best_surface_format() const {
      return surface_format::best_from_device_and_surface(&m_physical_device, &m_surface);
    }
    [[nodiscard]] swapchain best_swapchain_with_size(unsigned w, unsigned h) const {
      return swapchain::best_for(&m_physical_device, &m_surface, w, h);
    }
    [[nodiscard]] swapchain best_swapchain_with_size(extent_2d e) const {
      return best_swapchain_with_size(e.width(), e.height());
    }

    [[nodiscard]] constexpr const physical_device * physical_device() const noexcept {
      return &m_physical_device;
    }
    [[nodiscard]] constexpr const queue * unified_queue() const noexcept {
      return &m_unified_queue;
    }
    [[nodiscard]] constexpr auto unified_queue_family() const noexcept {
      return m_physical_device.unified_queue_family();
    }
  };
}
