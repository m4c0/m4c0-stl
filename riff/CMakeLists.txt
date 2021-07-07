m4c0_add_interface(
  TARGET m4c0-riff
  ALIAS m4c0::riff
  LIBRARIES m4c0::log
  )

m4c0_add_test(
  TARGET m4c0-riff-dump
  SOURCES tst/riff-dump.cpp
  LIBRARIES m4c0::riff
  )
m4c0_add_test(
  TARGET m4c0-riff-wavdump
  SOURCES tst/wav-dump.cpp
  LIBRARIES m4c0::riff
  )
m4c0_add_test(
  TARGET m4c0-riff-wavgen
  SOURCES tst/wav-gen.cpp
  LIBRARIES m4c0::riff
  )

m4c0_add_test(
  TARGET m4c0-riff-test-subreader
  ALIAS m4c0::riff::subreader
  SOURCES tst/test-subreader.cpp
  LIBRARIES m4c0::riff m4c0::test
  )
