#include "m4c0/osx/main.hpp"

int main(int argc, char ** argv) {
  static struct : public m4c0::osx::delegate {
    void start(const m4c0::objc::mtk_view * view) override {
    }
    void on_event(const m4c0::objc::ns_event * e) override {
    }
    void stop() override {
    }
  } d;
  m4c0::osx::main(argc, argv, &d);
}
