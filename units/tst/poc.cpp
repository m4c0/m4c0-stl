static constexpr auto operator""_inch(const char * value) noexcept {
  return m4c0::units::inch { value };
}
static constexpr auto operator""_mm(const char * value) noexcept {
  return m4c0::units::mm { value };
}

static_assert(1_inch == 25.4_mm);
static_assert(0.1_inch == 2.54_mm);

int main() {
}
