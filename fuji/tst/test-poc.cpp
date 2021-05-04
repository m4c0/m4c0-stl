#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/fuji/main_loop_thread.hpp"
#include "m4c0/vulkan/surface.hpp"

class my_main_loop : public m4c0::fuji::main_loop {
  void build_primary(cmd_buf cb) override {
  }
  void build_secondary(cmd_buf cb) override {
  }

  void run_device(const m4c0::fuji::device_context * ld) override {
    // Do some stuff...
    main_loop::run_device(ld);
    // Do more stuff...
  }
};

int main() {
  m4c0::vulkan::native_provider * native_stuff {}; // Get this somewhere else

  m4c0::fuji::main_loop_thread<my_main_loop> thread {};
  thread.start("My App", native_stuff);
  // Wait somewhere else
  thread.interrupt();
}
