#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_string.hpp"
#include "m4c0/objc/ns_window.hpp"

#include <CoreGraphics/CoreGraphics.h>

using namespace m4c0::objc;

cg_float ns_window::backing_scale_factor() {
  return objc_msg_send<cg_float>(self(), "backingScaleFactor");
}
ns_object ns_window::content_view() {
  void * obj = objc_msg_send<void *>(self(), "contentView");
  return ns_object { obj };
}
cg_point ns_window::mouse_location_outside_of_event_stream() {
  return objc_msg_send<cg_point>(self(), "mouseLocationOutsideOfEventStream");
}

void ns_window::set_accepts_mouse_moved_events(bool accepts) {
  objc_msg_send<void>(self(), "setAcceptsMouseMovedEvents:", accepts ? YES : NO);
}
void ns_window::set_collection_behavior(ns_window_collection_behavior cb) {
  objc_msg_send<void>(self(), "setCollectionBehavior:", cb);
}
void ns_window::set_content_view(const ns_object & view) {
  objc_msg_send<void>(self(), "setContentView:", view.self());
}
void ns_window::set_frame(cg_rect frame, bool display) {
  CGRect rect = CGRectMake(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height);
  objc_msg_send<void>(self(), "setFrame:display:", rect, display ? YES : NO);
}
void ns_window::set_style_mask(ns_window_style_mask mask) {
  objc_msg_send<void>(self(), "setStyleMask:", mask);
}
void ns_window::set_title(const char * title) {
  auto t = ns_string::with_cstring_utf8(title);
  objc_msg_send<void>(self(), "setTitle:", t.self());
}

void ns_window::center() {
  objc_msg_send<void>(self(), "center");
}
void ns_window::make_key_and_order_front() {
  objc_msg_send<void>(self(), "makeKeyAndOrderFront:", self());
}
