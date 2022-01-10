m4c0_add_interface(
  TARGET m4c0-containers
  LIBRARIES m4c0-core)

m4c0_add_test(
  TARGET test-m4c0-containers-constexpr
  SOURCES tst/zero_alloc_map.cpp
  LIBRARIES m4c0-containers)
