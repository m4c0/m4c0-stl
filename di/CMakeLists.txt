m4c0_add_library(
  TARGET m4c0-di
  ALIAS m4c0::di
  SOURCES
    src/config.cpp
    src/injector.cpp
    src/type_id.cpp
  LIBRARIES m4c0::core
  )

m4c0_add_test_subdirectory(tst)
