m4c0_add_interface(
  TARGET m4c0-riff
  LIBRARIES m4c0-core m4c0-io m4c0-log
  )

m4c0_add_test(
  TARGET m4c0-riff-wavdump
  SOURCES tst/wav-dump.cpp
  LIBRARIES m4c0-riff
  )
m4c0_add_test(
  TARGET m4c0-riff-wavgen
  SOURCES tst/wav-gen.cpp
  LIBRARIES m4c0-riff
  )

m4c0_add_test(
  TARGET m4c0-riff-test-parser
  SOURCES tst/test-parser.cpp
  LIBRARIES m4c0-riff m4c0-test
  )
