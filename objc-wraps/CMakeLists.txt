m4c0_add_library(
  TARGET m4c0-objc-wraps
  SOURCES 
    src/ca_metal_layer.cpp
    src/mtk_view.cpp
    src/ns_bundle.cpp
    src/ns_notification_center.cpp
    src/ns_object.cpp
    src/ns_string.cpp
  LIBRARIES m4c0-objc-bridge
  )

if(NOT(CMAKE_SYSTEM_NAME STREQUAL "iOS"))
  target_sources(m4c0-objc-wraps PRIVATE
    src/ns_application.cpp
    src/ns_application_delegate.cpp
    src/ns_menu.cpp
    src/ns_menu_item.cpp
    src/ns_window.cpp
    )

  m4c0_add_test(
    TARGET m4c0-test-objc-wraps-wrapping
    ALIAS m4c0::objc::wraps::wrapping
    SOURCES tst/test-wrapping.cpp
    LIBRARIES m4c0-objc-wraps
    )
endif()
