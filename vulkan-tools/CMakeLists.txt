m4c0_add_interface(
  TARGET m4c0-vulkan-tools
  ALIAS m4c0::vulkan::tools
  LIBRARIES
    m4c0::vulkan::actions
    m4c0::vulkan::objects
  )

m4c0_add_test(
  TARGET m4c0-vulkan-tools-test-poc
  SOURCES tst/test-poc.cpp
  LIBRARIES m4c0::vulkan::tools
  )
