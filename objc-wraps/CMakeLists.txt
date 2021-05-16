m4c0_add_library(
  TARGET m4c0-objc-wraps
  ALIAS m4c0::objc::wraps
  SOURCES 
    src/ns_application.cpp
    src/ns_object.cpp
  LIBRARIES m4c0::objc::bridge
  )
