#include "m4c0/casein/main.hpp"

std::unique_ptr<m4c0::casein::handler> m4c0::casein::main(const m4c0::native_handles * nh) {
  class my_handler : public handler {
  public:
  };
  return std::make_unique<my_handler>();
}
