#pragma once

#include "m4c0/casein/main.hpp"
#include "m4c0/droid/main.hpp"
#include "m4c0/native_handles.android.hpp"

namespace m4c0::casein::droid {
  using namespace m4c0::droid;

  class droid_provider : public native_handles {
    glue_app m_app;

  public:
    explicit constexpr droid_provider(glue_app app) : m_app(app) {
    }
    [[nodiscard]] ANativeWindow * window() const noexcept override {
      return m_app.window();
    }
    [[nodiscard]] AAssetManager * asset_manager() const noexcept override {
      return m_app.asset_manager();
    }
  };

  static void handle_command(glue_app app, glue_command cmd) {
    static droid_provider dp { app };
    static std::unique_ptr<m4c0::casein::handler> h;

    switch (cmd) {
    case init_window:
      h = m4c0::casein::main(&dp);
      break;
    case term_window:
      h.reset();
      break;
    default:
      break;
    }
  }
}
