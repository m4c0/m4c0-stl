#pragma once

namespace m4c0::objc {
  using cg_float = double;

  struct cg_point {
    cg_float x;
    cg_float y;
  };
  struct cg_size {
    cg_float width;
    cg_float height;
  };
  struct cg_rect {
    cg_point origin;
    cg_size size;
  };
}
