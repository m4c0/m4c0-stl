#include "m4c0/objc/ca_metal_layer.hpp"
#include "m4c0/objc/casts.hpp"

using namespace m4c0::objc;

void ca_metal_layer::set_contents_scale(cg_float scale) {
  objc_msg_send<void>(self(), "setContentsScale:", scale);
}
