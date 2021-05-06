#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/main_loop.hpp"
#include "m4c0/fuji/main_loop_thread.hpp"
#include "m4c0/vulkan/surface.hpp"

class my_objects {
public:
  void create(...) { // NOLINT
  }
  void render(...) { // NOLINT
  }
};

class my_main_loop : public m4c0::fuji::main_loop {
  my_objects * o {};

  void build_primary(VkCommandBuffer cb) override {
    o->create(cb); // NOLINT
  }
  void build_secondary(VkCommandBuffer cb) override {
    o->render(cb); // NOLINT
  }

  void run_device(const m4c0::fuji::device_context * ld) override {
    my_objects os {};
    o = &os;

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
