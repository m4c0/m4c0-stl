function(m4c0_add_interface)
  set(one_value_args TARGET ALIAS)
  set(multi_value_args LIBRARIES)
  cmake_parse_arguments(MAL "" "${one_value_args}" "${multi_value_args}" ${ARGN})

  add_library(${MAL_TARGET} INTERFACE)
  target_compile_features(${MAL_TARGET} INTERFACE cxx_std_20)
  target_include_directories(${MAL_TARGET} INTERFACE inc)
  target_link_libraries(${MAL_TARGET} INTERFACE ${MAL_LIBRARIES})

  add_library(${MAL_ALIAS} ALIAS ${MAL_TARGET})
endfunction()


function(m4c0_add_library)
  set(one_value_args TARGET ALIAS)
  set(multi_value_args SOURCES LIBRARIES)
  cmake_parse_arguments(MAL "" "${one_value_args}" "${multi_value_args}" ${ARGN})

  add_library(${MAL_TARGET} STATIC ${MAL_SOURCES})
  target_compile_features(${MAL_TARGET} PUBLIC cxx_std_20)
  target_include_directories(${MAL_TARGET} PUBLIC inc)
  target_link_libraries(${MAL_TARGET} PUBLIC ${MAL_LIBRARIES})

  add_library(${MAL_ALIAS} ALIAS ${MAL_TARGET})
endfunction()

