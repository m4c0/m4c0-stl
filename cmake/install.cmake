export(
  EXPORT m4c0-targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/m4c0-targets.cmake")

install(
  EXPORT m4c0-targets
  FILE m4c0-targets.cmake
  DESTINATION cmake/m4c0)

configure_file(cmake/m4c0-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/m4c0-config.cmake
  COPYONLY)

install(
  FILES cmake/m4c0-config.cmake
  DESTINATION cmake/m4c0)
