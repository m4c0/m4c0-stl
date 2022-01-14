#include "m4c0/ark/zip.iterator.hpp"
#include "m4c0/io/istr_reader.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char ** argv) { // NOLINT TODO: deal with exceptions?
  if (argc < 2) {
    std::cerr << "Missing file name\n";
    return 1;
  }

  std::ifstream file { argv[1] }; // NOLINT
  if (!file) {
    std::cerr << "File does not exist\n";
  }

  m4c0::io::istr_reader in { file };
  m4c0::ark::zip::zip_iterator it { &in };
  while (it) {
    auto cd = it.next();

    std::cout << "filename: ";
    for (auto c : cd.filename) {
      std::cout << c;
    }
    std::cout << "\n";

    std::cout << "offset: " << cd.method << "\n";
    std::cout << "compressed size: " << cd.compressed_size << "\n";
    std::cout << "uncompressed size: " << cd.uncompressed_size << "\n";
    std::cout << "\n";

    std::cout << "crc: " << std::hex << cd.uncompressed_size << "\n";
    std::cout << "flags: " << cd.flags << "\n";
    std::cout << "method: " << cd.method << "\n";

    std::cout << "\n";
    std::cout << "------\n";
  }
}
