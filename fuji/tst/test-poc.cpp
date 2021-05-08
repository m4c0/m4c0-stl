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
  void run_device(const m4c0::fuji::device_context * ld) override {
    my_objects os {};
    set_primary_cbb([&os](VkCommandBuffer cb) {
      os.create(cb); // NOLINT
    });
    set_secondary_cbb([&os](VkCommandBuffer cb) {
      os.create(cb); // NOLINT
    });

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
