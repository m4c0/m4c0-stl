#pragma once

#include "m4c0/casein/main.hpp"
#include "m4c0/native_handles.metal.hpp"
#include "m4c0/objc/ca_metal_layer.hpp"
#include "m4c0/objc/mtk_view.hpp"
#include "m4c0/osx/main.hpp"

namespace m4c0::casein::osx {
  class main : public m4c0::osx::delegate, public m4c0::native_handles {
    std::unique_ptr<m4c0::casein::handler> m_handler;
    objc::ca_metal_layer m_layer;
    objc::mtk_view m_view;

  protected:
    [[nodiscard]] constexpr const auto & view() const noexcept {
      return m_view;
    }

  public:
    void start(const m4c0::objc::mtk_view * view) override {
      m_layer = view->layer();
      m_handler = m4c0::casein::main(this);
    }
    void on_event(const m4c0::objc::ns_event * e) override {
    }
    void stop() override {
      m_handler.reset();
    }

    [[nodiscard]] CAMetalLayer * layer() const noexcept override {
      return m_layer.self();
    }
  };
}
