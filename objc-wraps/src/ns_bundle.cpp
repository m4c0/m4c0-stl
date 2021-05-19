#include "m4c0/objc/casts.hpp"
#include "m4c0/objc/ns_bundle.hpp"

using namespace m4c0::objc;

ns_bundle ns_bundle::main_bundle() {
  return ns_bundle { "NSBundle", "mainBundle", true };
}

ns_string ns_bundle::bundle_name() {
  auto * info = objc_msg_send<void *>(self(), "infoDictionary");

  auto key = ns_string::with_cstring_utf8("CFBundleName");
  auto * name = objc_msg_send<void *>(info, "objectForKey:", key.self());

  return ns_string { name };
}
