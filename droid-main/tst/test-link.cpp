#include "m4c0/droid/main.hpp"

#include <cstdint>

void m4c0::droid::handle_command(glue_app * app, glue_command cmd) {
  switch (cmd) {
  case init_window: {
    auto * wnd = app->window();
    // Do something with wnd
    break;
  }
  default:
    break;
  }
}

int main() {
}
