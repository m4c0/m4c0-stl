add_library(m4c0-ext-bandit INTERFACE)
target_include_directories(m4c0-ext-bandit INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/bandit)
add_library(m4c0::ext::bandit ALIAS m4c0-ext-bandit)

add_library(m4c0-ext-stb INTERFACE)
target_include_directories(m4c0-ext-stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb)
add_library(m4c0::ext::stb ALIAS m4c0-ext-stb)

add_library(m4c0-ext-volk STATIC)
target_include_directories(m4c0-ext-volk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/volk)
target_link_libraries(m4c0-ext-volk PUBLIC m4c0::ext::vulkan)
target_sources(m4c0-ext-volk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/volk/volk.c)
add_library(m4c0::ext::volk ALIAS m4c0-ext-volk)

add_library(m4c0-ext-vulkan INTERFACE)
target_include_directories(m4c0-ext-vulkan INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/vulkan-headers/include)
add_library(m4c0::ext::vulkan ALIAS m4c0-ext-vulkan)

if(ANDROID)
  target_compile_definitions(m4c0-ext-vulkan INTERFACE VK_USE_PLATFORM_ANDROID_KHR)
elseif(APPLE)
  target_compile_definitions(m4c0-ext-vulkan INTERFACE VK_USE_PLATFORM_METAL_EXT)
elseif(WIN32)
  target_compile_definitions(m4c0-ext-vulkan INTERFACE VK_USE_PLATFORM_WIN32_KHR)
else()
  message(ERROR "Unsupported platform")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
  set(MOLTENVK_TGZ ${CMAKE_CURRENT_BINARY_DIR}/MoltenVK.tgz)
  file(
    DOWNLOAD https://github.com/m4c0/molten-vk-build/releases/download/v1.1.0/MoltenVK.tgz ${MOLTENVK_TGZ}
    EXPECTED_HASH SHA1=a90397e81f313742baf4d38fa29b764cba7cab09
    )

  set(MOLTENVK_DIR Package/Release/MoltenVK/MoltenVK.xcframework)
  file(ARCHIVE_EXTRACT INPUT ${MOLTENVK_TGZ} PATTERNS ${MOLTENVK_DIR} VERBOSE)

  add_library(m4c0-ext-moltenvk INTERFACE)
  target_link_libraries(m4c0-ext-moltenvk INTERFACE
    "-framework CoreGraphics"
    "-framework Foundation"
    "-framework Metal"
    "-framework MetalKit"
    "-framework QuartzCore"
    "-framework UIKit"
    MoltenVK)
  add_library(m4c0::ext::moltenvk ALIAS m4c0-ext-moltenvk)

  # Most definitely we can link directly to the xcframework but I don't know how (or I can't properly use -F/-framework)
  string(TOLOWER "${CMAKE_OSX_SYSROOT}" SYSROOT_LC)
  string(FIND "${SYSROOT_LC}" "simulator" SIM_POS)
  if(SIM_POS EQUAL "-1")
    target_link_directories(m4c0-ext-moltenvk INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/${MOLTENVK_DIR}/ios-arm64)
  else()
    target_link_directories(m4c0-ext-moltenvk INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/${MOLTENVK_DIR}/ios-arm64_x86_64-simulator)
  endif()
endif()
