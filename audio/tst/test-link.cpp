#include "m4c0/audio.hpp"

#include <cmath>

using namespace m4c0::audio;

class my_prod : public producer {
public:
  void fill_buffer(std::span<float> data) override {
    static constexpr const float delta = 1.0F / streamer::rate; // 44Hz sound
    float acc = 0.0;
    for (auto & f : data) {
      f = std::sinf(acc);
      acc += delta;
    }
  }
};

int main() {
  streamer::create()->producer() = std::make_unique<my_prod>();
}
