#include "m4c0/objc/ca_metal_layer.hpp"
#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/mtk_view.hpp"

#if TARGET_OS_OSX
#include "m4c0/objc/ns_window.hpp"
#else
#include "m4c0/objc/ui_window.hpp"
#endif

using namespace m4c0::objc;

cg_rect mtk_view::bounds() const {
  return objc_msg_send<cg_rect>(self(), "bounds");
}
ca_metal_layer mtk_view::layer() const {
  return ca_metal_layer { objc_msg_send<void *>(self(), "layer") };
}
mtk_view::window_t mtk_view::window() const {
  auto * obj = objc_msg_send<void *>(self(), "window");
  return window_t { obj };
}
