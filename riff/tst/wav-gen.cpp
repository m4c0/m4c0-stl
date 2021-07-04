#include "m4c0/riff/types.hpp"

#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <type_traits>

using namespace m4c0::riff;

class writer {
protected:
  virtual void write(const void * buffer, unsigned len) = 0;

public:
  virtual void seekp(unsigned pos) = 0;
  virtual unsigned tellp() = 0;

  template<class Tp>
  auto write(const Tp & tp) -> std::enable_if_t<std::is_standard_layout_v<Tp> && !std::is_pointer_v<Tp>> {
    write(&tp, sizeof(Tp));
  }
};
class fs_writer : public writer {
  std::ostream & m_os;

public:
  explicit constexpr fs_writer(std::ostream & os) : m_os(os) {
  }

  void write(const void * buffer, unsigned len) override {
    m_os.write(static_cast<const char *>(buffer), len);
  }
  void seekp(unsigned pos) override {
    m_os.seekp(pos);
  }
  unsigned tellp() override {
    return m_os.tellp();
  }
};

class riff_writer {
  class chunk_writer {
    writer * m_w;
    unsigned m_start;

  public:
    chunk_writer(writer * w, fourcc_t fourcc) : m_w(w) {
      w->write(fourcc);
      w->write(static_cast<std::uint32_t>(0));
      m_start = w->tellp();
      std::cerr << "begin " << std::hex << fourcc << "\n";
    }
    ~chunk_writer() {
      auto end = m_w->tellp();
      std::cerr << "end at " << end << "\n";
      if (end % 2 == 1) {
        m_w->write('\0');
        std::cerr << "  with pad\n";
      }
      std::uint32_t len = end - m_start;
      std::cerr << "  len from " << m_start << " is " << len << "\n";
      m_w->seekp(m_start - sizeof(len));
      m_w->write(len);
      m_w->seekp(end + 1U & ~1U);
    }

    chunk_writer(const chunk_writer &) = delete;
    chunk_writer(chunk_writer &&) = delete;
    chunk_writer & operator=(const chunk_writer &) = delete;
    chunk_writer & operator=(chunk_writer &&) = delete;
  };

  chunk_writer m_hdr;
  writer * m_w;

public:
  riff_writer(writer * w, fourcc_t fourcc) : m_hdr(w, 'FFIR'), m_w(w) {
    w->write(fourcc);
  }

  template<class Tp>
  riff_writer & write(fourcc_t fourcc, Tp && data) {
    chunk_writer cw(m_w, fourcc);
    std::cerr << "  write " << std::hex << fourcc << " with " << sizeof(data) << "\n";
    m_w->write(data);
    return *this;
  }
};

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
  fs_writer w { std::cout };

  wav_fmt fmt {};
  std::array<std::uint8_t, freq> data {};

  riff_writer(&w, 'EVAW').write(' tmf', fmt).write('atad', data);
}
