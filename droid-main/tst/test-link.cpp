#include <cstdint>

class ANativeActivity;
extern "C" void ANativeActivity_onCreate(ANativeActivity * activity, void * saved_state, size_t saved_state_size);

int main(int argc, char ** argv) {
  if (argc < 100) return 0;

  // Just a silly linker hack
  ANativeActivity_onCreate(nullptr, nullptr, 0);
  return 0;
}
