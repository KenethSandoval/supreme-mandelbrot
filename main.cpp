#include <iostream>
#include <filesystem>
#include <fstream>
#include <complex>
#include <cmath>

constexpr auto WIDTH        = 1080;
constexpr auto HEIGHT       = 650;
constexpr auto FILE_SIZE    = WIDTH * HEIGHT;
constexpr auto RAD          = 50;
constexpr auto SCALE_FACTOR = 0.004;

void writeToFile(std::array<int, FILE_SIZE> &data)
{
  const std::filesystem::path path = "./out.ppm";
  std::ofstream out {path};
  out << "P6\n" << WIDTH << " " << HEIGHT << " " << "255\n";

  for(int i = 0; i < FILE_SIZE; ++i) {
    const char pixel[3] = {
      static_cast<const char>(data[i] >> (8 * 2) & 0xFF),
      static_cast<const char>(data[i] >> (8 * 1) & 0xFF),
      static_cast<const char>(data[i] >> (8 * 0) & 0xFF)
    };
    out.write(pixel, 3);
  }
  out.close();
}


int main() 
{
  std::array<int, FILE_SIZE> pixels{};
  writeToFile(pixels);
  return 0;
}
