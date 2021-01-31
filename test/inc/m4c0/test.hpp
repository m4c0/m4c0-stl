#pragma once

// This is just a convenience header for bandit tests. It saves 9 lines per
// test file - which is quite helpful after you write enough tests.

#include <bandit/bandit.h>

using namespace bandit;    // NOLINT
using namespace snowhouse; // NOLINT

int main(int argc, char ** argv) { // NOLINT
  return bandit::run(argc, argv);
}
