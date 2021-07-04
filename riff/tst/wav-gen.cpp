#include "m4c0/riff/builder.hpp"
#include "m4c0/riff/ostr_writer.hpp"
#include "m4c0/riff/types.hpp"

#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>

using namespace m4c0::riff;

constexpr const auto freq = 11025;
constexpr const auto bits = 8;
struct wav_fmt {
  using u16 = std::uint16_t;
  using u32 = std::uint32_t;

  u16 compression_code = 1; // PCM
  u16 channels = 1;         // Mono
  u32 frequency = freq;
  u32 sample_rate = freq;
  u16 block_align = 1;
  u16 bits_per_sample = bits;
};
constexpr const auto size_of_fmt = 16;
static_assert(sizeof(wav_fmt) == size_of_fmt);

int main() {
  ostr_writer w { std::cout };

  wav_fmt fmt {};
  std::array<std::uint8_t, freq> data {};

  riff_builder(&w, 'EVAW').write(' tmf', fmt).write('atad', data);
}
