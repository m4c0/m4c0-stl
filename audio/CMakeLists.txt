m4c0_add_library(
  TARGET m4c0-audio
  ALIAS m4c0::audio
  LIBRARIES m4c0::log
  )

if (APPLE)
  target_sources(m4c0-audio PRIVATE src/osx.cpp)
  target_link_libraries(m4c0-audio PUBLIC "-framework AudioToolbox")
elseif(WIN32)
  target_sources(m4c0-audio PRIVATE src/win.cpp)
endif()

m4c0_add_test(
  TARGET m4c0-test-audio-link
  LIBRARIES m4c0::audio
  SOURCES tst/test-link.cpp
  )
