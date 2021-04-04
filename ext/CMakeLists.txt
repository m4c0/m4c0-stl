add_library(m4c0-ext-bandit INTERFACE)
target_include_directories(m4c0-ext-bandit INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/bandit)
add_library(m4c0::ext::bandit ALIAS m4c0-ext-bandit)

add_library(m4c0-ext-volk STATIC)
target_include_directories(m4c0-ext-volk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/volk)
target_link_libraries(m4c0-ext-volk PUBLIC m4c0::ext::vulkan)
target_sources(m4c0-ext-volk PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/volk/volk.c)
add_library(m4c0::ext::volk ALIAS m4c0-ext-volk)

add_library(m4c0-ext-vulkan INTERFACE)
target_include_directories(m4c0-ext-vulkan INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/vulkan-headers/include)
add_library(m4c0::ext::vulkan ALIAS m4c0-ext-vulkan)

if(APPLE)
  target_compile_definitions(m4c0-ext-vulkan INTERFACE VK_USE_PLATFORM_METAL_EXT)
endif()
