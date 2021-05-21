#include "m4c0/objc/ca_metal_layer.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/objc/ns_window.hpp"

using namespace m4c0::objc;

cg_rect mtk_view::bounds() const {
  return objc_msg_send<cg_rect>(self(), "bounds");
}
ca_metal_layer mtk_view::layer() const {
  return ca_metal_layer { objc_msg_send<void *>(self(), "layer") };
}
ns_window mtk_view::window() const {
  auto * obj = objc_msg_send<void *>(self(), "window");
  return ns_window { obj };
}
