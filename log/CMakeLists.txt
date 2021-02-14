m4c0_add_library(
  TARGET m4c0-log
  ALIAS m4c0::log
  )

if (APPLE)
  enable_language(OBJC)
  target_sources(m4c0-log PRIVATE src/apple.cpp src/apple.m)
  target_compile_options(m4c0-log PRIVATE -fmodules -fobjc-arc)
elseif(WIN32)
  target_sources(m4c0-log PRIVATE src/windows.cpp)
elseif(ANDROID)
  target_sources(m4c0-log PRIVATE src/android.cpp)
  target_link_libraries(m4c0-log PUBLIC log)
endif()

m4c0_add_test_subdirectory(tst)

