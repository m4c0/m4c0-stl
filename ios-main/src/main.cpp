#include "m4c0/objc/middleware.hpp"

#include <string>

extern "C" {
#include "main.h"
}

int main(int argc, char ** argv) {
  auto & midware = m4c0::objc::middleware::instance();
  midware.create_for_protocol("UIApplicationDelegate");

  auto cls_name = midware.class_name_for_protocol("UIApplicationDelegate");
  objc_main(argc, argv, cls_name.c_str());
  return 0;
}
