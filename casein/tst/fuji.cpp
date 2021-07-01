#include "m4c0/casein/fuji.hpp"

struct loop : public m4c0::fuji::main_loop {
  void run_global(const m4c0::native_handles * nh) {
    m4c0::fuji::main_loop::run_global("MyApp", nh);
  }
};

std::unique_ptr<m4c0::casein::handler> m4c0::casein::main(const m4c0::native_handles * nh) {
  return std::make_unique<m4c0::casein::fuji_handler<loop>>(nh);
}
