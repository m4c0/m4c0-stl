#include "in_flight_list.hpp"
#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/frame_context.hpp"
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

void main_loop::run_frame(
    const m4c0::fuji::device_context * ld,
    const m4c0::fuji::swapchain_context * sc,
    const m4c0::fuji::in_flight * inf) {
  inf->wait_for_fence();

  const auto * frame = sc->acquire_next_frame(inf->image_available_semaphore());

  const auto * rp = ld->render_pass();

  auto * secondary = inf->build_secondary_command_buffer(rp, [this](auto cb) {
    build_secondary(cb);
  });
  auto * primary = frame->build_primary_command_buffer(rp, sc->render_extent(), secondary, [this](auto cb) {
    build_primary(cb);
  });

  inf->queue_submit(ld->unified_queue(), primary);
  sc->present(frame->index(), inf->render_finished_semaphore());
}

void main_loop::run_extent(const m4c0::fuji::device_context * ld, const m4c0::fuji::swapchain_context * sc) {
  in_flight_list in_flights { ld };

  try {
    while (true) {
      m_notifications.process();

      auto * inf = in_flights.flip();
      run_frame(ld, sc, inf);
    }
  } catch (const m4c0::vulkan::out_of_date_error &) {
    m4c0::log::debug("Refreshing state after swapchain changes");
  }
  m4c0::vulkan::actions::device_wait_idle();
}

void main_loop::run_device(const m4c0::fuji::device_context * ld) {
  while (true) {
    m4c0::fuji::swapchain_context sc { ld };
    run_extent(ld, &sc);
  }
}

void main_loop::run_global(const char * name, const m4c0::vulkan::native_provider * np) {
  try {
    m4c0::fuji::device_context ld { name, np };
    run_device(&ld);
  } catch (const interrupted_exception &) {
    m4c0::log::debug("Vulkan loop will end");
  }
}

void main_loop::interrupt() {
  m_notifications.enqueue([]() {
    m4c0::vulkan::actions::device_wait_idle();
    throw interrupted_exception();
  });
}
