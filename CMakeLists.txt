cmake_minimum_required(VERSION 3.17..3.19)
project(m4c0-stl
  VERSION 1.0.0
  DESCRIPTION "m4c0's C++ Standard Library"
  LANGUAGES C CXX)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (ANDROID)
  find_program(ADB adb REQUIRED)
endif()
function(m4c0_add_test TEST TARGET)
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

add_subdirectory(core)
add_subdirectory(di)
add_subdirectory(ext)
add_subdirectory(test)

