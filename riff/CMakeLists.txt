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
