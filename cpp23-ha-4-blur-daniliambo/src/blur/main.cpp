#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::vector;

struct Color {
  double r, g, b;

  Color();
  Color(double r, double g, double b);
  ~Color();
};

class Image {
public:
  Image(int width, int height);
  ~Image();

  Color GetColor(int x, int y) const;
  void SetColor(const Color &color, int x, int y);

  void Read(const char *path);

  void Export(const char *path) const;

  int get_width() const;

  int get_height() const;

private:
  int m_width;
  int m_height;
  std::vector<Color> m_colors;
};
Color::Color() : r(0), g(0), b(0) {}

Color::Color(double r, double g, double b) : r(r), g(g), b(b) {}
Color::~Color() {}

Image::Image(int width, int height)
    : m_width(width), m_height(height),
      m_colors(std::vector<Color>(width * height)) {}

Image::~Image() {}

Color Image::GetColor(int x, int y) const { return m_colors[y * m_width + x]; }

int Image::get_width() const { return m_width; };

int Image::get_height() const { return m_height; };

void Image::SetColor(const Color &color, int x, int y) {
  m_colors[y * m_width + x].r = color.r;
  m_colors[y * m_width + x].g = color.g;
  m_colors[y * m_width + x].b = color.b;
}

void Image::Read(const char *path) {

  std::ifstream f;
  f.open(path, std::ios::in | std::ios::binary);

  if (!f.is_open()) {
    std::cout << "File could not be opened" << std::endl;
    return;
  }

  const int fileHeaderSize = 14;
  const int informationHeaderSize = 40;

  unsigned char fileHeader[fileHeaderSize];

  f.read(reinterpret_cast<char *>(fileHeader), fileHeaderSize);

  if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
    std::cout << "The specified path is not a bitmap image" << std::endl;
    return;
  }

  unsigned char InformationHeader[informationHeaderSize];
  f.read(reinterpret_cast<char *>(InformationHeader), informationHeaderSize);

  // int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16)
  // +
  //                (fileHeader[5] << 24);

  m_width = InformationHeader[4] + (InformationHeader[5] << 8) +
            (InformationHeader[6] << 16) + (InformationHeader[7] << 24);
  m_height = InformationHeader[8] + (InformationHeader[9] << 8) +
             (InformationHeader[10] << 16) + (InformationHeader[11] << 24);

  m_colors.resize(m_width * m_height);

  const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      unsigned char color[3];
      f.read(reinterpret_cast<char *>(color), 3);

      m_colors[y * m_width + x].r = static_cast<double>(color[2]) / 255.0f;
      m_colors[y * m_width + x].g = static_cast<double>(color[1]) / 255.0f;
      m_colors[y * m_width + x].b = static_cast<double>(color[0]) / 255.0f;
    }
    f.ignore(paddingAmount);
  }
  f.close();
  // std::cout << "File read" << std::endl;
}

void Image::Export(const char *path) const {
  std::ofstream f;
  // writing out, writing binary
  f.open(path, std::ios::out | std::ios::binary);

  if (!f.is_open()) {
    std::cout << "File could not be opened!" << std::endl;
  }

  unsigned char bmpPad[3] = {0, 0, 0};
  const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

  const int fileHeaderSize = 14;
  const int informationHeaderSize = 40;
  const int fileSize = fileHeaderSize + informationHeaderSize +
                       m_width * m_height * 3 + paddingAmount * m_height;

  unsigned char fileHeader[fileHeaderSize];

  // File type
  fileHeader[0] = 'B';
  fileHeader[1] = 'M';

  // File size
  fileHeader[2] = fileSize;
  fileHeader[3] = fileSize >> 8;
  fileHeader[4] = fileSize >> 16;
  fileHeader[5] = fileSize >> 24;

  // Reserved 1
  fileHeader[6] = 0;
  fileHeader[7] = 0;

  // Reserved 2
  fileHeader[8] = 0;
  fileHeader[9] = 0;

  // Pixel data offset
  fileHeader[10] = fileHeaderSize + informationHeaderSize;
  fileHeader[11] = 0;
  fileHeader[12] = 0;
  fileHeader[13] = 0;

  unsigned char InformationHeader[informationHeaderSize];

  // Header size
  InformationHeader[0] = informationHeaderSize;
  InformationHeader[1] = 0;
  InformationHeader[2] = 0;
  InformationHeader[3] = 0;

  // Image width
  InformationHeader[4] = m_width;
  InformationHeader[5] = m_width >> 8;
  InformationHeader[6] = m_width >> 16;
  InformationHeader[7] = m_width >> 24;

  // Image height
  InformationHeader[8] = m_height;
  InformationHeader[9] = m_height >> 8;
  InformationHeader[10] = m_height >> 16;
  InformationHeader[11] = m_height >> 24;

  // Planes
  InformationHeader[12] = 1;
  InformationHeader[13] = 0;

  // Bits per pixel(RGB)
  InformationHeader[14] = 24;
  InformationHeader[15] = 0;

  InformationHeader[16] = 0;
  InformationHeader[17] = 0;
  InformationHeader[18] = 0;
  InformationHeader[19] = 0;
  InformationHeader[20] = 0;
  InformationHeader[21] = 0;
  InformationHeader[22] = 0;
  InformationHeader[23] = 0;
  InformationHeader[24] = 0;
  InformationHeader[25] = 0;
  InformationHeader[26] = 0;
  InformationHeader[27] = 0;
  InformationHeader[28] = 0;
  InformationHeader[29] = 0;
  InformationHeader[30] = 0;
  InformationHeader[31] = 0;
  InformationHeader[32] = 0;
  InformationHeader[33] = 0;
  InformationHeader[34] = 0;
  InformationHeader[35] = 0;
  InformationHeader[36] = 0;
  InformationHeader[37] = 0;
  InformationHeader[38] = 0;
  InformationHeader[39] = 0;

  // because of pointers
  f.write(reinterpret_cast<char *>(fileHeader), fileHeaderSize);
  f.write(reinterpret_cast<char *>(InformationHeader), informationHeaderSize);

  for (int y = 0; y < m_height; ++y) {
    for (int x = 0; x < m_width; ++x) {
      // static_cast keeps the value changes the type
      unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
      unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
      unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

      unsigned char color[] = {b, g, r};

      f.write(reinterpret_cast<char *>(color), 3);
    }
    f.write(reinterpret_cast<char *>(bmpPad), paddingAmount);
  }
  f.close();

  // std::cout << "File created\n";
}

// File header
// DIB header
// Pixel array

struct ParamsParser {
public:
  ParamsParser() = default;
  ParamsParser(string input, string output, int r)
      : input_(input), output_(output), r_(r){};

  string get_input() { return input_; }
  string get_output() { return output_; }
  int get_r() { return r_; }

  void set_input(string val) { input_ = val; }
  void set_output(string val) { output_ = val; }
  void set_r(int val) { r_ = val; }

private:
  string input_;
  string output_;
  int r_;
};

ParamsParser process_arguments(int argc, char **argv) {
  ParamsParser params;
  if (argc != 7) {
    throw std::invalid_argument("Wrong number of arguments!");
  }

  for (int i = 1; i < argc; i += 2) {
    string arg0 = static_cast<string>(argv[i]);
    string arg1 = static_cast<string>(argv[i + 1]);
    if (arg0.rfind('-', 0) == 0 && arg1.rfind('-', 0) != 0) {
      if (arg0 == "-i") {
        params.set_input(arg1);
      } else if (arg0 == "-o") {
        params.set_output(arg1);
      } else if (arg0 == "-r") {
        int val = std::stoi(arg1);
        if ((val > 0) && (val % 2 != 0)) {
          params.set_r(val);
        } else {
          throw std::invalid_argument("Wrong r!");
        }
      } else {
        throw std::invalid_argument("Unexpected argument!");
      }
    } else {
      throw std::invalid_argument("Wrong sequence of arguments!");
    }
  }
  return params;
};

vector<double> gaussian_kernel(int ksize) {
  double sigma = 0.3 * ((ksize - 1) * 0.5 - 1) + 0.8;
  vector<double> res;
  double sum = 0;
  for (int i = 0; i < ksize; ++i) {
    double val = exp(-(std::pow(i - (ksize - 1) / 2, 2) / (2 * pow(sigma, 2))));
    sum += val;
    res.push_back(val);
  }
  double alpha = 1 / sum;
  for (int i = 0; i < ksize; ++i) {
    res[i] *= alpha;
  }
  return res;
}

Image solution(Image &img, int radius) {
  int width = img.get_width();
  int height = img.get_height();

  vector<double> kernel = gaussian_kernel(radius);

  Image result(width, height);
  int threshold = radius / 2;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double_t r_sum = 0.0;
      double_t g_sum = 0.0;
      double_t b_sum = 0.0;
      for (int k = 0; k < radius; k++) {
        int col = j - radius / 2 + k;
        if (col >= 0 && col < width) {
          r_sum += img.GetColor(i, col).r * kernel[k];
          g_sum += img.GetColor(i, col).g * kernel[k];
          b_sum += img.GetColor(i, col).b * kernel[k];
        }
      }
      result.SetColor(Color(r_sum, g_sum, b_sum), i, j);
    }
  }

  for (int j = threshold; j < width - threshold; j++) {
    for (int i = threshold; i < height - threshold; i++) {
      double_t sumR = 0.0;
      double_t sumG = 0.0;
      double_t sumB = 0.0;
      for (int k = 0; k < radius; k++) {
        int row = i - radius / 2 + k;
        if (row >= 0 && row < height) {
          sumR += result.GetColor(row, j).r * kernel[k];
          sumG += result.GetColor(row, j).g * kernel[k];
          sumB += result.GetColor(row, j).b * kernel[k];
        }
      }
      img.SetColor(Color(sumR, sumG, sumB), i, j);
    }
  }
  return img;
};

int main(int argc, char **argv) {
  ParamsParser params;
  try {
    params = process_arguments(argc, argv);
  } catch (const std::invalid_argument &e) {
    std::cerr << e.what() << endl;
    return 1;
  };

  Image img_input(0, 0);
  img_input.Read(params.get_input().c_str());

  Image img_output = solution(img_input, params.get_r());

  img_output.Export(params.get_output().c_str());
}
