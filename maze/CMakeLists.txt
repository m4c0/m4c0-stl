m4c0_add_interface(
  TARGET m4c0-maze
  ALIAS m4c0::maze
  )

m4c0_add_test(
  ALIAS m4c0::maze::model
  TARGET m4c0-test-maze-model
  SOURCES tst/model.cpp
  LIBRARIES m4c0::maze m4c0::test)

m4c0_add_test(
  ALIAS m4c0::maze::view::grid
  TARGET m4c0-test-maze-view-grid
  SOURCES tst/view_grid.cpp
  LIBRARIES m4c0::maze m4c0::test)
