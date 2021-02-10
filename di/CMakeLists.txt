add_library(m4c0-di STATIC
  src/config.cpp
  src/injector.cpp
  src/type_id.cpp
  )
target_compile_features(m4c0-di PRIVATE cxx_std_20)
target_include_directories(m4c0-di PUBLIC inc)
target_link_libraries(m4c0-di PUBLIC m4c0::core)

add_library(m4c0::di ALIAS m4c0-di)

m4c0_add_test_subdirectory(tst)
