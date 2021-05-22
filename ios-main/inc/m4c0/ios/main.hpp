#pragma once

#include "m4c0/objc/mtk_view.hpp"

namespace m4c0::ios {
  class delegate {
  public:
    virtual void start(const objc::mtk_view * view) = 0;
    virtual void stop() = 0;
  };

  int main(int argc, char ** argv, delegate * d);
}
