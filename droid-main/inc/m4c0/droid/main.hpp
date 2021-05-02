#pragma once

class android_app;

struct AAssetManager;
struct ANativeWindow;

namespace m4c0::droid {
  class glue_app {
    android_app * m_glue;

  public:
    glue_app(android_app * app) : m_glue(app) {
    }

    [[nodiscard]] AAssetManager * asset_manager();
    [[nodiscard]] ANativeWindow * window();
  };

  // This is in the same order as defined by the "glue" to allow a direct conversion from an int
  enum glue_command : int {
    input_changed,
    init_window,
    term_window,
    window_resized,
    window_redraw_needed,
    content_rect_changed,
    gained_focus,
    lost_focus,
    config_changed,
    low_memory,
    start,
    resume,
    save_state,
    pause,
    stop,
    destroy,
  };

  void handle_command(glue_app * app, glue_command cmd);
}
