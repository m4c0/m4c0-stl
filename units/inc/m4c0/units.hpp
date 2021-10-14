#pragma once

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

    [[nodiscard]] static constexpr meter from_inch(const uint64_t value) noexcept {
      return meter(value * 2.54 * 10e-2); // NOLINT
    }
    [[nodiscard]] static constexpr meter from_mil(const uint64_t value) noexcept {
      return meter(value * 2.54 * 10e-5); // NOLINT
    }
    [[nodiscard]] static constexpr meter from_mm(const uint64_t value) noexcept {
      return meter(value * 10e-3); // NOLINT
    }
    [[nodiscard]] static constexpr meter from_um(const uint64_t value) noexcept {
      return meter(value * 10e-6); // NOLINT
    }

    [[nodiscard]] static constexpr meter nil() noexcept {
      return meter(0);
    }
  };
}
namespace m4c0::units::literals {
  static constexpr auto operator""_inch(const uint64_t value) noexcept {
    return meter::from_inch(value);
  }
  static constexpr auto operator""_mil(const uint64_t value) noexcept {
    return meter::from_mil(value);
  }
  static constexpr auto operator""_mm(const uint64_t value) noexcept {
    return meter::from_mm(value);
  }
  static constexpr auto operator""_um(const uint64_t value) noexcept {
    return meter::from_um(value);
  }
}
