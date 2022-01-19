#include "m4c0/ark/deflate.buffer.hpp"
#include "m4c0/ark/deflate.symbols.hpp"

#include <optional>
#include <string_view>
#include <variant>

using namespace m4c0::ark::deflate;

static_assert(buffer {}.empty());

static constexpr auto visit(const symbols::symbol & s) noexcept {
  buffer b {};
  return std::visit(b, s) ? std::optional { b } : std::nullopt;
}
static_assert(!visit(symbols::end {}));
static_assert(visit(symbols::raw { 'y' }));

static constexpr auto visit_and_read(buffer & b, uint8_t c) {
  if (!b(symbols::raw { c })) return false;
  if (b.empty()) return false;
  if (b.read() != c) return false;
  return b.empty();
}
static constexpr auto visit_and_read(buffer & b, std::string_view str, unsigned dist) {
  if (!b(symbols::repeat { static_cast<unsigned int>(str.length()), dist })) return false;
  for (uint8_t c : str) {
    if (b.empty()) return false;
    if (b.read() != c) return false;
  }
  return b.empty();
}

static_assert([] {
  buffer b {};
  if (!visit_and_read(b, 'y')) return false;
  if (!visit_and_read(b, 'u')) return false;
  if (!visit_and_read(b, 'p')) return false;
  return true;
}());
static_assert([] {
  buffer b {};
  if (!visit_and_read(b, 't')) return false;
  if (!visit_and_read(b, 'e')) return false;
  if (!visit_and_read(b, 's')) return false;
  if (!visit_and_read(b, "te", 3)) return false;
  return true;
}());
static_assert([] {
  buffer b {};
  if (!visit_and_read(b, 't')) return false;
  if (!visit_and_read(b, 'e')) return false;
  if (!visit_and_read(b, 's')) return false;
  if (!visit_and_read(b, "te", 3)) return false;
  if (!visit_and_read(b, ' ')) return false;
  if (!visit_and_read(b, "test", 6)) return false; // NOLINT
  return true;
}());
