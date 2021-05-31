#include "m4c0/casein/main.osx.hpp"
#include "m4c0/osx/main.hpp"

int main(int argc, char ** argv) {
  static m4c0::casein::osx::main d;
  return m4c0::osx::main(argc, argv, &d);
}
