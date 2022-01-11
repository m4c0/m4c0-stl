m4c0_add_interface(
  TARGET m4c0-espresso
  LIBRARIES 
    m4c0-containers
    m4c0-io
  )

m4c0_add_test(
  TARGET m4c0-test-espresso-poc
  LIBRARIES m4c0-espresso
  SOURCES 
    tst/constant.cpp
    tst/poc.cpp
  )
