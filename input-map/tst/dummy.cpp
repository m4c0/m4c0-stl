#include "m4c0/input_map/layouts.hpp"

template<class Key>
void show_on_screen(Key name) {
}

int main() {
  m4c0::input_map::layout::xbox x {};
  x.buttons.top = [](bool /*down*/) {
  };
  show_on_screen(x.buttons.top.name());
}
