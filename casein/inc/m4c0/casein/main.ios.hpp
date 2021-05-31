#pragma once

#include "m4c0/casein/main.hpp"
#include "m4c0/ios/main.hpp"
#include "m4c0/native_handles.metal.hpp"
#include "m4c0/objc/ca_metal_layer.hpp"
#include "m4c0/objc/mtk_view.hpp"

namespace m4c0::casein::ios {
  class main : public m4c0::ios::delegate, public m4c0::native_handles {
    std::unique_ptr<m4c0::casein::handler> m_handler;
    CAMetalLayer * m_layer {};

  public:
    void start(const m4c0::objc::mtk_view * view) override {
      m_layer = view->layer().self();
      m_handler = m4c0::casein::main(this);
    }
    void stop() override {
      m_handler.reset();
    }

    [[nodiscard]] CAMetalLayer * layer() const noexcept override {
      return m_layer;
    }
  };
}
