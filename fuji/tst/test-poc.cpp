#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/fuji/main_loop_thread.hpp"
#include "m4c0/native_handles.hpp"
#include "m4c0/vulkan/surface.hpp"

class my_objects : public m4c0::fuji::main_loop_listener {
public:
  explicit my_objects(const m4c0::vulkan::tools::logical_device * /*ld*/) {
    // Create stuff
  }

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

int main() {
  m4c0::native_handles * native_stuff {}; // Get this somewhere else

  m4c0::fuji::main_loop_thread<m4c0::fuji::main_loop_with_stuff<my_objects>> thread {};
  thread.start("My App", native_stuff);
  // Wait somewhere else
  thread.interrupt();
}
