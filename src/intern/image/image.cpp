#include "image/image.h"

using namespace nash;

Image::Image(const std::string & filename) : width(0), height(0), numChannels(0) {
  std::string absPath = Path::getAbsolutePathTo(filename);
  data = stbi_load(absPath.c_str(), &width, &height, &numChannels, 4);
  if (!data) {
    throw std::runtime_error("Cannot load file " + absPath);
  }
}

Image::~Image() {
  stbi_image_free(data);
}
