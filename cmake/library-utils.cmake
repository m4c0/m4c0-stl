function(_m4c0_add_library)
  set(one_value_args ALIAS SCOPE TARGET TYPE)
  set(multi_value_args LIBRARIES)
  cmake_parse_arguments(MAL "" "${one_value_args}" "${multi_value_args}" ${ARGN})

  add_library(${MAL_TARGET} ${MAL_TYPE})
  target_compile_features(${MAL_TARGET} ${MAL_SCOPE} cxx_std_20)
  target_include_directories(${MAL_TARGET} ${MAL_SCOPE} inc)
  target_link_libraries(${MAL_TARGET} ${MAL_SCOPE} ${MAL_LIBRARIES})

  add_library(${MAL_ALIAS} ALIAS ${MAL_TARGET})
endfunction()

function(m4c0_add_interface)
  set(one_value_args TARGET ALIAS)
  set(multi_value_args LIBRARIES)
  cmake_parse_arguments(MAL "" "${one_value_args}" "${multi_value_args}" ${ARGN})

  _m4c0_add_library(
    TARGET ${MAL_TARGET}
    ALIAS ${MAL_ALIAS}
    LIBRARIES ${MAL_LIBRARIES}
    TYPE INTERFACE
    SCOPE INTERFACE)
endfunction()

function(m4c0_add_library)
  set(options OBJCXX)
  set(one_value_args TARGET ALIAS)
  set(multi_value_args SOURCES LIBRARIES)
  cmake_parse_arguments(MAL "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

  _m4c0_add_library(
    TARGET ${MAL_TARGET}
    ALIAS ${MAL_ALIAS}
    LIBRARIES ${MAL_LIBRARIES}
    TYPE STATIC
    SCOPE PUBLIC)
  target_sources(${MAL_TARGET} PRIVATE ${MAL_SOURCES})

  if(MAL_OBJCXX)
    target_compile_options(${MAL_TARGET} PRIVATE -fmodules -fobjc-arc)
    set_target_properties(${MAL_TARGET} PROPERTIES
      OBJCXX_STANDARD 20
      OBJCXX_STANDARD_REQUIRED TRUE
      OBJCXX_EXTENSIONS FALSE
      )
  endif()
endfunction()

