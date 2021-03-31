#pragma once

#include "m4c0/objc/inject.hpp"

namespace m4c0::ios {
  struct inject_app_did_finish_launch_with_options : objc::static_inject {
    inject_app_did_finish_launch_with_options();
  };
}
