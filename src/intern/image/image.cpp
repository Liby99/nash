#include "image/image.h"
#include <stb_image.h>
#include <stdexcept>

using namespace nash;

Image::Image(const std::string &filename) : width(0), height(0), numChannels(0) {
  std::string absPath = Path::getAbsolutePathTo(filename);
  data = stbi_load(absPath.c_str(), &width, &height, &numChannels, STBI_rgb_alpha);
  if (!data) {
    throw std::runtime_error("Cannot load file " + absPath);
  }
}

Image::~Image() { stbi_image_free(data); }

Vector4u Image::getColor(int i, int j) const {
  int start = (j * width + i) * 4;
  return Vector4u(data[start], data[start + 1], data[start + 2], data[start + 3]);
}