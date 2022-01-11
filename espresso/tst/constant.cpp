#include "m4c0/espresso/constant.hpp"
#include "m4c0/io/ce_reader.hpp"

/*
m4c0::io::ce_reader {
"j\x01\x00\x03\x28\x29\x56\x01\x00"
};
*/

template<auto N>
static constexpr auto read(const char (&in)[N]) { // NOLINT
  m4c0::io::ce_reader r { in };
  return m4c0::espresso::constant::read(&r);
}

static_assert([] {
  read("\x0a\x00\x03\x00\x0c");
  read("\x07\x00\x0d");
  read("\x01\x00\x06\x3c\x69\x6e\x69\x74\x3e");
  return true;
}());
