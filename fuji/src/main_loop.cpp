#include "in_flight_list.hpp"
#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/fuji/frames_list.hpp"
#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/fuji/swapchain_context.hpp"
#include "m4c0/log.hpp"
#include "m4c0/vulkan/base_command.hpp"
#include "m4c0/vulkan/device_wait_idle.hpp"
#include "m4c0/vulkan/execute_commands.hpp"
#include "m4c0/vulkan/out_of_date_error.hpp"
#include "m4c0/vulkan/render_pass_guard.hpp"

#include <thread>

using namespace m4c0::fuji;

void main_loop::run_extent(const m4c0::fuji::device_context * ld, const m4c0::fuji::swapchain_context * sc) {
  in_flight_list in_flights { ld };
  frames_list frames { ld, sc };
  m_listener->on_render_extent_change(sc->render_extent());

  try {
    while (true) {
      m_notifications.process();

      auto * inf = in_flights.flip();
      inf->wait_for_fence();

      auto index = sc->acquire_next_frame(inf->image_available_semaphore());
      const auto * frame = frames.at(index);

      const auto * rp = ld->render_pass();
      auto * secondary = inf->build_secondary_command_buffer(rp, [this](auto cb) {
        m_listener->build_secondary_command_buffer(cb);
      });
      auto * primary = frame->build_primary_command_buffer(rp, sc->render_extent(), secondary, [this](auto cb) {
        m_listener->build_primary_command_buffer(cb);
      });

      inf->queue_submit(ld->unified_queue(), primary);

      sc->present(index, inf->render_finished_semaphore());
    }
  } catch (const m4c0::vulkan::out_of_date_error &) {
    m4c0::log::debug("Refreshing state after swapchain changes");
  }
  m4c0::vulkan::actions::device_wait_idle();
}

void main_loop::run_device(const m4c0::fuji::device_context * ld) {
  try {
    while (true) {
      m4c0::fuji::swapchain_context sc { ld };
      run_extent(ld, &sc);
    }
  } catch (const interrupted_exception &) {
    m4c0::log::debug("Vulkan loop will end");
  }
}

void main_loop::run_global(const char * name, const m4c0::vulkan::native_provider * np) {
  m4c0::fuji::device_context ld { name, np };
  run_device(&ld);
}

void main_loop::interrupt() {
  m_notifications.enqueue([]() {
    m4c0::vulkan::actions::device_wait_idle();
    throw interrupted_exception();
  });
}
