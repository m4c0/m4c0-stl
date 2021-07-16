#pragma once

#include <algorithm>
#include <array>
#include <optional>
#include <type_traits>

namespace m4c0 {
  template<typename KeyTp, typename ValueTp>
  struct pair {
    KeyTp key;
    ValueTp value;
  };
  template<typename KeyTp, typename ValueTp>
  pair(KeyTp, ValueTp) -> pair<KeyTp, ValueTp>;

  // This has the simplest implementation possible for a constexpr thing
  template<typename KeyTp, typename ValueTp, auto MaxElements>
  class ce_map {
    static_assert(std::is_trivially_copyable_v<KeyTp>);
    static_assert(std::is_trivially_copyable_v<ValueTp>);

    static constexpr const auto arbitrary_max_length = 16;
    static_assert(
        MaxElements < arbitrary_max_length,
        "You have hit an arbitrary limit. Please check if this scales to the limit you need");

    std::array<KeyTp, MaxElements> m_keys {};
    std::array<ValueTp, MaxElements> m_values {};

  public:
    using pair_t = pair<KeyTp, ValueTp>;

    constexpr ce_map() = default;
    constexpr ce_map(std::initializer_list<pair_t> i) {
      std::transform(i.begin(), i.end(), m_keys.begin(), [](auto p) {
        return p.key;
      });
      std::transform(i.begin(), i.end(), m_values.begin(), [](auto p) {
        return p.value;
      });
    }

    [[nodiscard]] constexpr const ValueTp & at(const KeyTp & key) const {
      auto * it = std::find(m_keys.begin(), m_keys.end(), key);
      if (it == m_keys.end()) {
        throw std::runtime_error("Map overflow");
      }
      auto idx = it - m_keys.begin();
      return m_values.at(idx);
    }
    [[nodiscard]] constexpr const ValueTp & operator[](const KeyTp & key) const {
      return at(key);
    }

    [[nodiscard]] constexpr ValueTp get_or_else(const KeyTp & key, ValueTp def = {}) const {
      auto * it = std::find(m_keys.begin(), m_keys.end(), key);
      if (it == m_keys.end()) {
        return def;
      }
      auto idx = it - m_keys.begin();
      return m_values.at(idx);
    }
  };

  template<typename KeyTp, typename ValueTp, typename... Others>
  ce_map(pair<KeyTp, ValueTp>, Others...) -> ce_map<KeyTp, ValueTp, sizeof...(Others) + 1>;
}
