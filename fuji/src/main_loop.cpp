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
#include "m4c0/vulkan/queue_submit.hpp"
#include "m4c0/vulkan/render_pass_guard.hpp"

#include <thread>

using namespace m4c0::fuji;

main_loop::cmd_buf main_loop::run_primary(
    const m4c0::fuji::device_context * ld,
    const m4c0::fuji::swapchain_context * sc,
    const m4c0::fuji::frame_context * f,
    main_loop::cmd_buf secondary) {
  auto primary = f->begin_primary_command_buffer();

  build_primary(primary.command_buffer());

  m4c0::vulkan::tools::render_pass_guard rpg { primary.command_buffer(),
                                               f->framebuffer(),
                                               ld->render_pass(),
                                               sc->render_extent() };
  m4c0::vulkan::cmd::execute_commands(primary.command_buffer()).add_command_buffer(secondary).now();
  return primary.command_buffer();
}

main_loop::cmd_buf main_loop::run_secondary(const m4c0::fuji::device_context * ld, const m4c0::fuji::in_flight * inf) {
  auto guard = inf->begin_secondary_command_buffer(ld->render_pass());
  build_secondary(guard.command_buffer());
  return guard.command_buffer();
}

void main_loop::run_frame(
    const m4c0::fuji::device_context * ld,
    const m4c0::fuji::swapchain_context * sc,
    const m4c0::fuji::in_flight * inf) {
  const auto * frame = sc->acquire_next_frame(inf->image_available_semaphore());

  auto * secondary = run_secondary(ld, inf);
  auto * primary = run_primary(ld, sc, frame, secondary);

  m4c0::vulkan::actions::queue_submit()
      .with_queue(ld->unified_queue())
      .with_command_buffer(primary)
      .with_fence(inf->fence())
      .with_wait_semaphore(inf->image_available_semaphore())
      .with_signal_semaphore(inf->render_finished_semaphore())
      .now();

  sc->present(frame->index(), inf->render_finished_semaphore());
}

void main_loop::run_extent(const m4c0::fuji::device_context * ld, const m4c0::fuji::swapchain_context * sc) {
  in_flight_list in_flights { ld };

  try {
    while (true) {
      m_notifications.process();

      auto * inf = in_flights.flip();
      inf->wait_for_fence();

      run_frame(ld, sc, inf);
    }
  } catch (const m4c0::vulkan::out_of_date_error &) {
    m4c0::log::debug("Refreshing state after swapchain changes");
  }
  m4c0::vulkan::actions::device_wait_idle();
}

void main_loop::run_device(const m4c0::fuji::device_context * ld) {
  while (m_window_width == 0) {
    std::this_thread::yield();
  }
  while (true) {
    m4c0::fuji::swapchain_context sc { ld, { m_window_width, m_window_height } };
    run_extent(ld, &sc);
  }
}

void main_loop::run_global(const char * name, m4c0::vulkan::native_ptr_t native_ptr) {
  try {
    m4c0::fuji::device_context ld { name, native_ptr };
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
void main_loop::window_resized(unsigned w, unsigned h) {
  m_window_height = h;
  m_window_width = w;
}
