#include "m4c0/units.hpp"

using namespace m4c0::units::literals;

// TODO: find a better way to avoid "nolint" when constexpr-test using magic constants

static_assert(20_mm == 20_mm);       // NOLINT
static_assert(20_mm != 21_mm);       // NOLINT
static_assert(21_mm == 21_mm);       // NOLINT
static_assert(121_inch == 121_inch); // NOLINT
static_assert(121_inch != 122_inch); // NOLINT
static_assert(29_mil == 29_mil);     // NOLINT
static_assert(29_mil != 27_mil);     // NOLINT

static_assert(1_mm == 1000_um);      // NOLINT
static_assert(1_inch == 25400_um);   // NOLINT
static_assert(10_inch == 10000_mil); // NOLINT
static_assert(10_mil == 254_um);     // NOLINT

static_assert(1_um * 1000 == 1_mm); // NOLINT
static_assert(1_mm / 1000 == 1_um); // NOLINT

static_assert(1_um * 25400 == 1_inch); // NOLINT
static_assert(1_inch / 25400 == 1_um); // NOLINT

static_assert(12_mm * -1 == -12_mm); // NOLINT

static_assert(1_mm + 1_inch == 26400_um); // NOLINT
static_assert(1_inch - 1_mm == 24400_um); // NOLINT

int main() {
}
