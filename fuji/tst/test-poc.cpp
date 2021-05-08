#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/fuji/main_loop_thread.hpp"
#include "m4c0/vulkan/surface.hpp"

class my_objects : public m4c0::fuji::main_loop_listener {
public:
  void build_primary_command_buffer(VkCommandBuffer cb) override {
    // Transfer textures, etc
  }
  void build_secondary_command_buffer(VkCommandBuffer cb) override {
    // Render stuff
  }
  void on_render_extent_change(m4c0::vulkan::extent_2d e) override {
    // Update uniforms
  }
};

class my_main_loop : public m4c0::fuji::main_loop {
  void run_device(const m4c0::fuji::device_context * ld) override {
    my_objects os {};
    listener() = &os;
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
