#include <cmath>
#include <cstdlib>
#include <limits>

namespace m4c0::units {
  class meter {
    // TODO: Implement a "fixed point" version or something
    double m_value;

    constexpr explicit meter(double v) : m_value(v) {
    }

  public:
    [[nodiscard]] constexpr bool operator==(const meter & o) const noexcept {
      constexpr const auto epsilon = std::numeric_limits<double>::epsilon();
      constexpr const auto min = std::numeric_limits<double>::min();

      const auto x = m_value;
      const auto y = o.m_value;
      const auto abs_m = x - y > 0 ? x - y : y - x;
      const auto abs_p = x + y > 0 ? x + y : -x - y;
      return abs_m <= epsilon * abs_p || abs_m < min;
    }

    [[nodiscard]] constexpr meter operator+(const meter & o) const noexcept {
      return meter(m_value + o.m_value);
    }
    [[nodiscard]] constexpr meter operator-(const meter & o) const noexcept {
      return meter(m_value - o.m_value);
    }

    [[nodiscard]] constexpr meter operator-() const noexcept {
      return meter(-m_value);
    }
    [[nodiscard]] constexpr meter operator*(double value) const noexcept {
      return meter(m_value * value);
    }
    [[nodiscard]] constexpr meter operator/(double value) const noexcept {
      return meter(m_value / value);
    }

    [[nodiscard]] static constexpr meter from_inch(uint64_t value) noexcept {
      return meter(value * 2.54 * 10e-2); // NOLINT
    }
    [[nodiscard]] static constexpr meter from_mil(uint64_t value) noexcept {
      return meter(value * 2.54 * 10e-5); // NOLINT
    }
    [[nodiscard]] static constexpr meter from_mm(uint64_t value) noexcept {
      return meter(value * 10e-3); // NOLINT
    }
    [[nodiscard]] static constexpr meter from_um(uint64_t value) noexcept {
      return meter(value * 10e-6); // NOLINT
    }
  };
}
namespace m4c0::units::literals {
  static constexpr auto operator""_inch(uint64_t value) noexcept {
    return meter::from_inch(value);
  }
  static constexpr auto operator""_mil(uint64_t value) noexcept {
    return meter::from_mil(value);
  }
  static constexpr auto operator""_mm(uint64_t value) noexcept {
    return meter::from_mm(value);
  }
  static constexpr auto operator""_um(uint64_t value) noexcept {
    return meter::from_um(value);
  }
}

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
