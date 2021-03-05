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

  set(options WIN32)
  set(one_value_args TARGET ALIAS)
  set(multi_value_args LIBRARIES SOURCES)
  cmake_parse_arguments(MAT "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

  add_executable(${MAT_TARGET} ${MAT_SOURCES})
  target_link_libraries(${MAT_TARGET} PRIVATE ${MAT_LIBRARIES})

  if(MAT_WIN32)
    set_target_properties(${MAT_TARGET} PROPERTIES WIN32_EXECUTABLE TRUE)
  endif()

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
    add_test(${MAT_ALIAS} ${ADB} shell /data/local/tmp/${MAT_TARGET})
  endif()
endfunction()
