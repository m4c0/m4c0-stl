m4c0_add_library(
  TARGET m4c0-assets
  ALIAS m4c0::assets
  LIBRARIES m4c0::native-handles
  )

if(ANDROID)
  target_sources(m4c0-assets PRIVATE src/simple_asset.android.cpp)
  target_link_libraries(m4c0-assets PUBLIC android)
elseif(APPLE)
  target_sources(m4c0-assets PRIVATE src/simple_asset.apple.cpp)
  target_link_libraries(m4c0-assets PUBLIC "-framework CoreFoundation")
elseif(WIN32)
  target_sources(m4c0-assets PRIVATE src/simple_asset.win32.cpp)
endif()

m4c0_add_test(
  TARGET m4c0-test-assets-link
  LIBRARIES m4c0::assets
  SOURCES tst/test-link.cpp
  )
