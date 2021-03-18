#include "m4c0/input_map/layouts.hpp"

int main() {
  m4c0::input_map::layout::xbox x {};
  x.buttons.top = [](bool /*down*/) {
  };
}
