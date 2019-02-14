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
