m4c0_add_interface(
  TARGET m4c0-ark
  LIBRARIES m4c0-io
  )

m4c0_add_test(
  TARGET m4c0-test-ark
  SOURCES tst/zip.cpp
  LIBRARIES m4c0-ark
  )
