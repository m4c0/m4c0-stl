#include "m4c0/audio.hpp"

#include <aaudio/AAudio.h>

class droid_streamer : public m4c0::audio::streamer {
  static aaudio_data_callback_result_t callback(
      AAudioStream * /*stream*/,
      void * user,
      void * audio,
      int32_t number_frames) {
    auto * str = static_cast<droid_streamer *>(user);
    auto * f_data = static_cast<float *>(audio);
    auto f_len = static_cast<unsigned>(number_frames);
    if (str->producer() != nullptr) str->producer()->fill_buffer({ f_data, f_len });
    return AAUDIO_CALLBACK_RESULT_CONTINUE;
  }

  AAudioStream * m_aas {};

public:
  droid_streamer() {
    using builder_t = std::unique_ptr<AAudioStreamBuilder, decltype(&AAudioStreamBuilder_delete)>;

    AAudioStreamBuilder * builder {};
    AAudio_createStreamBuilder(&builder);
    builder_t guard { builder, &AAudioStreamBuilder_delete };

    AAudioStreamBuilder_setSharingMode(builder, AAUDIO_SHARING_MODE_EXCLUSIVE);
    AAudioStreamBuilder_setPerformanceMode(builder, AAUDIO_PERFORMANCE_MODE_LOW_LATENCY);
    AAudioStreamBuilder_setFormat(builder, AAUDIO_FORMAT_PCM_FLOAT);
    AAudioStreamBuilder_setChannelCount(builder, 1);
    AAudioStreamBuilder_setSampleRate(builder, streamer::rate);
    AAudioStreamBuilder_setDataCallback(builder, &callback, this);

    AAudioStream * stream {};
    AAudioStreamBuilder_openStream(builder, &stream);
    AAudioStream_requestStart(stream);
  }
  ~droid_streamer() override {
    AAudioStream_close(m_aas);
  }

  droid_streamer(const droid_streamer &) = delete;
  droid_streamer(droid_streamer &&) = delete;
  droid_streamer & operator=(const droid_streamer &) = delete;
  droid_streamer & operator=(droid_streamer &&) = delete;
};

std::unique_ptr<m4c0::audio::streamer> m4c0::audio::streamer::create() {
  return std::make_unique<droid_streamer>();
}
