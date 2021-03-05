option(M4C0_ENABLE_TESTS "Enable tests for the m4c0-stl package" ON)

if (M4C0_ENABLE_TESTS)
  enable_testing()
  if (ANDROID)
    find_program(ADB adb REQUIRED)
  endif()
endif()

function(m4c0_add_test)
  if(NOT M4C0_ENABLE_TESTS)
    return()
  endif()

  set(one_value_args TARGET ALIAS)
  set(multi_value_args LIBRARIES SOURCES)
  cmake_parse_arguments(MAT "" "${one_value_args}" "${multi_value_args}" ${ARGN})

  add_executable(${MAT_TARGET} ${MAT_SOURCES})
  target_link_libraries(${MAT_TARGET} PRIVATE ${MAT_LIBRARIES})

  if(NOT MAT_ALIAS)
    return()
  endif()

  if(NOT ANDROID)
    add_test(${MAT_ALIAS} ${MAT_TARGET})
  else()
    add_custom_command(
      TARGET ${MAT_TARGET}
      POST_BUILD
      COMMAND ${ADB} push $<TARGET_FILE:${MAT_TARGET}> /data/local/tmp/${MAT_TARGET}
      )
    add_test(${MAT_TEST} ${ADB} shell /data/local/tmp/${MAT_TARGET})
  endif()
endfunction()

macro(m4c0_add_test_subdirectory)
  if (M4C0_ENABLE_TESTS)
    add_subdirectory(tst)
  endif()
endmacro()

