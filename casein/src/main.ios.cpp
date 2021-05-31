#include "m4c0/casein/main.ios.hpp"
#include "m4c0/ios/main.hpp"

int main(int argc, char ** argv) {
  static m4c0::casein::ios::main d;
  return m4c0::ios::main(argc, argv, &d);
}
