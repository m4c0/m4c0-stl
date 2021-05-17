#pragma once

namespace m4c0::objc {
  struct cg_point {
    float x;
    float y;
  };
  struct cg_size {
    float width;
    float height;
  };
  struct cg_rect {
    cg_point origin;
    cg_size size;
  };
}
