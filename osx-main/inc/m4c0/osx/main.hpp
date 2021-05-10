#pragma once

namespace m4c0::osx {
  class delegate {
  public:
    virtual void start(void * view) = 0;
    virtual void stop() = 0;
  };

  int main(int argc, char ** argv, delegate * d);
}
