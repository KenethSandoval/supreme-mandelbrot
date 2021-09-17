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

int isInMandelbrot(std::complex<double> c) 
{
  std::complex z(0.0, 0.1);
  for(int i = 0; i < 255; ++i) {
    z = std::pow(z, 2.0) + c;
    if(abs(z) >= 2) return i;
  }
  return 0;
}

void fillMandelbrot(std::array<int, FILE_SIZE> &data)
{
  for(int i = 0; i < HEIGHT; ++i) {
    for(int j = 0; j < WIDTH; ++j) {
      double dx = (j - 720) * SCALE_FACTOR;
      double dy = (i - 320) * SCALE_FACTOR;
      std::complex<double> number = std::complex(dx, dy);
      const unsigned char intensity = isInMandelbrot(number);
      auto n = (double)intensity;
      double a = 0.1;
     
      data[i* WIDTH + j] = (int((0.5 * sin(a * n) + 0.5) * 255) << (8 * 2)) +
                           (int((0.5 * sin(a * n + 1) + 0.5f) * 255) << (8 * 1)) +
                           (int((0.5 * sin(a * n + 2) + 0.5f) * 255) << (8 * 0)); 
    }
  }

}

int main() 
{
  std::array<int, FILE_SIZE> pixels{};
  fillMandelbrot(pixels);
  writeToFile(pixels);
  return 0;
}
