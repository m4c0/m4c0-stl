#include "m4c0/objc/ca_metal_layer.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/objc/ns_window.hpp"

using namespace m4c0::objc;

ca_metal_layer mtk_view::layer() {
  return ca_metal_layer { objc_msg_send<void *>(self(), "layer") };
}
ns_window mtk_view::window() {
  auto * obj = objc_msg_send<void *>(self(), "window");
  return ns_window { obj };
}
