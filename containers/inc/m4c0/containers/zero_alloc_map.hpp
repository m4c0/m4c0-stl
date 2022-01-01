#pragma once

#include "m4c0/concepts.hpp"

#include <array>
#include <stdexcept>

namespace m4c0::containers::details {
  struct zero_alloc_map_defaults {
    // Random prime numbers - If bigger than that, std::map is probably better
    static constexpr const auto bucket_count = 97;
    static constexpr const auto bucket_size = 5;
  };
}
namespace m4c0::containers {
  template<
      hashable Key,
      typename Value,
      size_t BCount = details::zero_alloc_map_defaults::bucket_count,
      size_t BSize = details::zero_alloc_map_defaults::bucket_size>
  class zero_alloc_map {
  public:
    static constexpr const auto bucket_count = BCount;
    static constexpr const auto bucket_size = BSize;
    static constexpr const auto array_size = bucket_count * bucket_size;

    using key_t = Key;
    using value_t = Value;
    using entry_t = std::pair<key_t, value_t>;

  private:
    class bucket {
      std::array<entry_t, bucket_size> m_data {};
      std::size_t m_count {};

    public:
      [[nodiscard]] constexpr auto begin() const noexcept {
        return m_data.begin();
      }
      [[nodiscard]] constexpr auto end() const noexcept {
        return m_data.begin() + m_count;
      }
      [[nodiscard]] constexpr auto begin() noexcept {
        return m_data.begin();
      }
      [[nodiscard]] constexpr auto end() noexcept {
        return m_data.begin() + m_count;
      }
      [[nodiscard]] constexpr auto & alloc(const key_t & k) {
        if (m_count == bucket_size) throw std::runtime_error("bucket overflow");
        auto & e = m_data.at(m_count++);
        e.first = k;
        return e.second;
      }
    };

    std::array<bucket, array_size> m_buckets;

    [[nodiscard]] constexpr std::size_t bucket_index_of(key_t key) const noexcept {
      return std::hash<key_t>()(key) % bucket_count;
    }

  public:
    [[nodiscard]] constexpr bool contains(key_t key) const {
      for (const auto & kv : m_buckets.at(bucket_index_of(key))) {
        if (kv.first == key) return true;
      }
      return false;
    }
    [[nodiscard]] constexpr const value_t * get(key_t key) const {
      for (const auto & kv : m_buckets.at(bucket_index_of(key))) {
        if (kv.first == key) return &kv.second;
      }
      return nullptr;
    }

    [[nodiscard]] constexpr const value_t & operator[](key_t key) const {
      if (auto * v = get(key)) {
        return *v;
      }
      throw std::runtime_error("trying to access non-existent element");
    }
    [[nodiscard]] constexpr value_t & operator[](key_t key) {
      auto & bucket = m_buckets.at(bucket_index_of(key));
      for (auto & kv : bucket) {
        if (kv.first == key) return kv.second;
      }
      return bucket.alloc(key);
    }
  };
}
