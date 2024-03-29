function(_m4c0_add_library)
  set(one_value_args ALIAS SCOPE TARGET TYPE)
  set(multi_value_args LIBRARIES)
  cmake_parse_arguments(MAL "" "${one_value_args}" "${multi_value_args}" ${ARGN})

  add_library(${MAL_TARGET} ${MAL_TYPE})
  # We need this distinction until MSVC allows constexpr virtual in C++20
  target_compile_features(${MAL_TARGET} ${MAL_SCOPE} $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:cxx_std_20>)
  target_compile_options(${MAL_TARGET} ${MAL_SCOPE} $<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>) 
  target_link_libraries(${MAL_TARGET} ${MAL_SCOPE} ${MAL_LIBRARIES})

  if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/inc/m4c0)
    target_include_directories(${MAL_TARGET} ${MAL_SCOPE}
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
      $<INSTALL_INTERFACE:include>)
    install(DIRECTORY inc/m4c0 TYPE INCLUDE COMPONENT ${MAL_TARGET})
  endif()
  install(TARGETS ${MAL_TARGET} EXPORT m4c0-targets COMPONENT ${MAL_TARGET})
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
  set(multi_value_args SOURCES LIBRARIES PRIVATE_LIBRARIES)
  cmake_parse_arguments(MAL "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

  # TODO: PUBLIC/PRIVATE scopes needs to be revisited. I think this leads to duplicatecompilation
  _m4c0_add_library(
    TARGET ${MAL_TARGET}
    ALIAS ${MAL_ALIAS}
    LIBRARIES ${MAL_LIBRARIES}
    TYPE STATIC
    SCOPE PUBLIC)
  target_link_libraries(${MAL_TARGET} PRIVATE ${MAL_PRIVATE_LIBRARIES})
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

