m4c0_add_interface(
  TARGET m4c0-ark
  LIBRARIES 
    m4c0-containers
    m4c0-io
  )

m4c0_add_test(
  TARGET m4c0-test-ark
  SOURCES
    tst/bitstream.cpp
    tst/deflate.cpp
    tst/deflate.buffer.cpp
    tst/deflate.details.cpp
    tst/deflate.symbols.cpp
    tst/huffman.cpp
    tst/zip.cpp
    tst/zip.cdir.cpp
    tst/zip.eocd.cpp
    tst/zip.local.cpp
  LIBRARIES m4c0-ark
  )

m4c0_add_test(
  TARGET m4c0-ark-zipdump
  SOURCES tst/zip.dump.cpp
  LIBRARIES m4c0-ark
  )
