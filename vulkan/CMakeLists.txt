m4c0_add_library(
  TARGET m4c0-vulkan
  ALIAS m4c0::vulkan
  SOURCES
    src/command_pool.cpp
    src/debug_utils_messenger.cpp
    src/device.cpp
    src/fence.cpp
    src/image.cpp
    src/instance.cpp
    src/physical_device.cpp
    src/queue.cpp
    src/render_pass.cpp
    src/safe_calls.cpp
    src/sampler.cpp
    src/semaphore.cpp
    src/surface.cpp
    src/surface_format.cpp
  LIBRARIES
    m4c0::core
    m4c0::log
  )

if(ANDROID)
  target_compile_definitions(m4c0-vulkan PRIVATE M4C0_VULKAN_SURFACE_EXTENSION_NAME=VK_KHR_ANDROID_SURFACE_EXTENSION_NAME)
  target_sources(m4c0-vulkan PRIVATE src/surface.android.cpp)
elseif(APPLE)
  target_compile_definitions(m4c0-vulkan PRIVATE M4C0_VULKAN_SURFACE_EXTENSION_NAME=VK_EXT_METAL_SURFACE_EXTENSION_NAME)
  target_sources(m4c0-vulkan PRIVATE src/surface.metal.cpp)
elseif(WIN32)
  target_compile_definitions(m4c0-vulkan PRIVATE M4C0_VULKAN_SURFACE_EXTENSION_NAME=VK_KHR_WIN32_SURFACE_EXTENSION_NAME)
  target_sources(m4c0-vulkan PRIVATE src/surface.win32.cpp)
else()
  message(ERROR "Unsupported platform")
endif()

# So far, it was easier to add a static MoltenVK instead of codesigning it in iOS
if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
  target_link_libraries(m4c0-vulkan PUBLIC m4c0::vulkan::static)
else()
  target_link_libraries(m4c0-vulkan PUBLIC m4c0::vulkan::dynamic)

  m4c0_add_test(
    TARGET m4c0-test-vulkan-poc
    SOURCES tst/test-poc.cpp
    LIBRARIES m4c0::vulkan)
endif()
