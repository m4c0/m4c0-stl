#include "m4c0/containers/unique_ptr.hpp"

using m4c0::containers::unique_ptr;

using uint = unique_ptr<int>;

static_assert(!uint());
static_assert(uint(new int { 3 }));
static_assert((uint() = uint::make(3)));
static_assert(*uint(new int { 3 }) == 3);
