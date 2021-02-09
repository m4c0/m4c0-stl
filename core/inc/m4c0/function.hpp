#pragma once

#include <array>
#include <memory>
#include <stdexcept>

namespace m4c0 {
  template<typename Fn>
  class function;

  template<typename Result, typename... Args>
  class function<Result(Args...)> {
    using self_t = function<Result(Args...)>;

    static constexpr const auto buffer_size = 4 * sizeof(void *);
    using buffer = std::array<char, buffer_size>;
    using wrapper = Result (*)(void *, Args &&...);
    using deleter = void (*)(void *);

    template<typename Tp>
    static constexpr const bool is_same_v = std::is_same_v<std::remove_cvref_t<Tp>, self_t>;
    template<typename Tp>
    static constexpr const bool fits = sizeof(std::remove_cvref_t<Tp>) < buffer_size;

    buffer m_buffer;
    wrapper m_wrapper;
    deleter m_deleter;

    void reset() {
      m_wrapper = [](void * /*unused*/, Args &&... /*unused*/) -> Result {
        throw std::runtime_error("moved function called");
      };
      m_deleter = nullptr;
    }

  public:
    function() {
      m_wrapper = [](void * /*unused*/, Args &&... /*unused*/) -> Result {
        throw std::runtime_error("empty function called");
      };
      m_deleter = nullptr;
    }
    template<typename Fn, typename = std::enable_if_t<!is_same_v<Fn> && fits<Fn>, void>>
    function(Fn && fn) { // NOLINT TODO: Should we "explicit" this?
      ::new (&m_buffer) Fn(std::forward<Fn>(fn));
      m_wrapper = [](void * ptr, Args &&... args) {
        auto p = std::launder(static_cast<Fn *>(ptr));
        return (*p)(std::forward<Args>(args)...);
      };
      m_deleter = [](void * ptr) {
        auto p = std::launder(static_cast<Fn *>(ptr));
        std::destroy_at<Fn>(p);
      };
    }
    template<typename Fn, typename = std::enable_if_t<!is_same_v<Fn> && !fits<Fn>, void>>
    function(Fn fn) {                                   // NOLINT TODO: Should we "explicit" this?
      *reinterpret_cast<Fn **>(&m_buffer) = new Fn(fn); // NOLINT
      m_wrapper = [](void * ptr, Args &&... args) {
        return (**static_cast<Fn **>(ptr))(std::forward<Args>(args)...);
      };
      m_deleter = [](void * ptr) {
        std::default_delete<Fn>()(*static_cast<Fn **>(ptr));
      };
    }
    ~function() { // NOLINT(bugprone-exception-escape)
      if (m_deleter != nullptr) m_deleter(&m_buffer);
      m_wrapper = [](void * /*unused*/, Args &&... /*unused*/) -> Result {
        // Fires an exception if this instance is used after being deleted
        throw std::runtime_error("deleted function called");
      };
    }

    function(function && o) noexcept : m_buffer(o.m_buffer), m_wrapper(o.m_wrapper), m_deleter(o.m_deleter) {
      o.reset();
    }
    function & operator=(function && o) noexcept {
      if (&o == this) return *this;
      if (m_deleter != nullptr) m_deleter(&m_buffer);
      m_buffer = o.m_buffer;
      m_wrapper = o.m_wrapper;
      m_deleter = o.m_deleter;
      o.reset();
      return *this;
    }

    function(const function &) = delete;
    function & operator=(const function &) = delete;

    template<class... As>
    Result operator()(As &&... args) {
      return m_wrapper(&m_buffer, std::forward<Args>(args)...);
    }
  };
}
