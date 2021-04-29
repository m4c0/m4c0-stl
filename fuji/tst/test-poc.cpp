#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/fuji/main_loop_thread.hpp"
#include "m4c0/vulkan/surface.hpp"

class my_main_loop : public m4c0::fuji::main_loop {
  void run_device(const m4c0::fuji::device_context * ld) override {
    // Do some stuff...
    main_loop::run_device(ld);
    // Do more stuff...
  }
};

int main() {
  m4c0::vulkan::native_ptr_t native_stuff {}; // Get this somewhere else

  m4c0::fuji::main_loop_thread<my_main_loop> thread { "My App", native_stuff };
  thread.window_resized(800, 600); // NOLINT
  // Wait somewhere else
  thread.interrupt();
}
