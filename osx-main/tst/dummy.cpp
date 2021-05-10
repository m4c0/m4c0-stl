#include "m4c0/osx/main.hpp"

int main(int argc, char ** argv) {
  static struct : public m4c0::osx::delegate {
    void start(void * view) override {
    }
    void stop() override {
    }
  } d;
  m4c0::osx::main(argc, argv, &d);
}
