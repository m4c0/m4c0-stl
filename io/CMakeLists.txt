m4c0_add_interface(
  TARGET m4c0-io
  ALIAS m4c0::io
  )

m4c0_add_test(
  TARGET m4c0-io-test-subreader
  ALIAS m4c0::io::subreader
  SOURCES tst/test-subreader.cpp
  LIBRARIES m4c0::io m4c0::test
  )
m4c0_add_test(
  TARGET m4c0-io-test-ce-reader
  SOURCES tst/test-ce-reader.cpp
  LIBRARIES m4c0::io
  )
