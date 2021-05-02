#include "glue/android_native_app_glue.h"
#include "m4c0/droid/main.hpp"

static void handle_command(android_app * app, int32_t cmd) {
  m4c0::droid::glue_app ga { app };
  m4c0::droid::glue_command gc { cmd };
  m4c0::droid::handle_command(&ga, gc);

  if (cmd == APP_CMD_STOP) {
    ANativeActivity_finish(app->activity);
  }
}

static void process_command(android_app * app) {
  int events;
  android_poll_source * source;
  if (ALooper_pollAll(0, nullptr, &events, (void **)&source) >= 0) {
    if (source != nullptr) {
      source->process(app, source);
    }
  }
}

void android_main(android_app * app) {
  app->onAppCmd = handle_command;

  do {
    process_command(app);
  } while (app->destroyRequested == 0);
}
