#include "m4c0/osx/main.hpp"

const char * m4c0::osx::view_classname() {
  return "MTKView";
}
const char * m4c0::osx::view_delegate_classname() {
  return "Dummy";
}
const char * m4c0::osx::window_delegate_classname() {
  return "Dummy";
}
