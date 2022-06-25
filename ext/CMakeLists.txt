function(m4c0_add_ext_interface)
  cmake_parse_arguments(M "" "NAME;INCLUDE" "" ${ARGN})

  set(target "m4c0-ext-${M_NAME}")

  add_library(${target} INTERFACE)
  target_include_directories(${target} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${M_NAME}/${M_INCLUDE}>
    $<INSTALL_INTERFACE:include/${M_NAME}/${M_INCLUDE}>)
  install(DIRECTORY ${M_NAME} TYPE INCLUDE COMPONENT ${target})
  install(TARGETS ${target} EXPORT m4c0-targets COMPONENT ${target})
endfunction()

m4c0_add_ext_interface(NAME bandit)
m4c0_add_ext_interface(NAME stb)
m4c0_add_ext_interface(NAME vulkan-headers INCLUDE include)

add_library(m4c0-ext-volk STATIC)
target_include_directories(m4c0-ext-volk PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/volk>
  $<INSTALL_INTERFACE:include/volk>)
target_link_libraries(m4c0-ext-volk PUBLIC m4c0-ext-vulkan-headers)
target_sources(m4c0-ext-volk PRIVATE volk/volk.c)
install(DIRECTORY volk TYPE INCLUDE COMPONENT ext-volk)
install(TARGETS m4c0-ext-volk EXPORT m4c0-targets COMPONENT ext-volk)

if(ANDROID)
  target_compile_definitions(m4c0-ext-vulkan-headers INTERFACE VK_USE_PLATFORM_ANDROID_KHR)
elseif(APPLE)
  target_compile_definitions(m4c0-ext-vulkan-headers INTERFACE VK_USE_PLATFORM_METAL_EXT)
elseif(WIN32)
  target_compile_definitions(m4c0-ext-vulkan-headers INTERFACE VK_USE_PLATFORM_WIN32_KHR)
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
  install(TARGETS m4c0-ext-moltenvk EXPORT m4c0-targets COMPONENT m4c0-ext-moltenvk)

  # Most definitely we can link directly to the xcframework but I don't know how (or I can't properly use -F/-framework)
  string(TOLOWER "${CMAKE_OSX_SYSROOT}" SYSROOT_LC)
  string(FIND "${SYSROOT_LC}" "simulator" SIM_POS)
  if(SIM_POS EQUAL "-1")
    target_link_directories(m4c0-ext-moltenvk INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/${MOLTENVK_DIR}/ios-arm64)
  else()
    target_link_directories(m4c0-ext-moltenvk INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/${MOLTENVK_DIR}/ios-arm64_x86_64-simulator)
  endif()
endif()
