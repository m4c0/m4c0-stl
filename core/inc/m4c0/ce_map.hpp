#pragma once

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
    static_assert(std::is_trivial_v<KeyTp>);
    static_assert(std::is_trivial_v<ValueTp>);

    using key_t = std::optional<KeyTp>;

    static constexpr const auto arbitrary_max_length = 16;
    static_assert(
        MaxElements < arbitrary_max_length,
        "You have hit an arbitrary limit. Please check if this scales to the limit you need");

    std::array<key_t, MaxElements> m_keys {};
    std::array<ValueTp, MaxElements> m_values {};

  public:
    constexpr ce_map() = default;
    constexpr ce_map(std::initializer_list<pair<KeyTp, ValueTp>> i) {
      for (auto & it : i) {
        at(it.key) = it.value;
      }
    }

    [[nodiscard]] constexpr ValueTp & at(const KeyTp & key) {
      auto * it = std::find(m_keys.begin(), m_keys.end(), key_t { key });
      if (it == m_keys.end()) {
        it = std::find(m_keys.begin(), m_keys.end(), key_t {});
        if (it == m_keys.end()) {
          throw std::runtime_error("Map overflow");
        }
        *it = key;
      }
      auto idx = it - m_keys.begin();
      return m_values.at(idx);
    }
    [[nodiscard]] constexpr const ValueTp & at(const KeyTp & key) const {
      auto * it = std::find(m_keys.begin(), m_keys.end(), key_t { key });
      if (it == m_keys.end()) {
        throw std::runtime_error("Map overflow");
      }
      auto idx = it - m_keys.begin();
      return m_values.at(idx);
    }
    [[nodiscard]] constexpr ValueTp & operator[](const KeyTp & key) {
      return at(key);
    }
    [[nodiscard]] constexpr const ValueTp & operator[](const KeyTp & key) const {
      return at(key);
    }
  };
  template<typename KeyTp, typename ValueTp, typename... Others>
  ce_map(pair<KeyTp, ValueTp>, Others...) -> ce_map<KeyTp, ValueTp, sizeof...(Others) + 1>;
}
