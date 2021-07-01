m4c0_add_library(
  TARGET m4c0-vulkan-tools
  ALIAS m4c0::vulkan::tools
  LIBRARIES
    m4c0::vulkan::actions
    m4c0::vulkan::commands
    m4c0::vulkan::objects
  PRIVATE_LIBRARIES
    m4c0::assets
  SOURCES
    src/staged_image.cpp
  )

if(NOT(CMAKE_SYSTEM_NAME STREQUAL "iOS"))
  m4c0_add_test(
    TARGET m4c0-vulkan-tools-test-poc
    SOURCES tst/test-poc.cpp
    LIBRARIES m4c0::assets m4c0::vulkan::tools
    )
endif()
