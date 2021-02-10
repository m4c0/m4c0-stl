option(M4C0_ENABLE_TESTS "Enable tests for the m4c0-stl package" ON)

if (M4C0_ENABLE_TESTS)
  enable_testing()
  if (ANDROID)
    find_program(ADB adb REQUIRED)
  endif()
endif()

function(m4c0_add_test TEST TARGET)
  if(NOT M4C0_ENABLE_TESTS)
    return()
  endif()

  if(NOT ANDROID)
    add_test(${TEST} ${TARGET})
  else()
    add_custom_command(
      TARGET ${TARGET}
      POST_BUILD
      COMMAND ${ADB} push $<TARGET_FILE:${TARGET}> /data/local/tmp/${TARGET}
      )
    add_test(${TEST} ${ADB} shell /data/local/tmp/${TARGET})
  endif()
endfunction()

macro(m4c0_add_test_subdirectory)
  if (M4C0_ENABLE_TESTS)
    add_subdirectory(tst)
  endif()
endmacro()

