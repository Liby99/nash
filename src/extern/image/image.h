#ifndef IMAGE_H
#define IMAGE_H

// Import stb image
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "utility/path.h"
#include <string>

namespace nash {
class Image {
public:
  int width, height, numChannels;
  Image(const std::string &filename);
  ~Image();

private:
  unsigned char *data;
};
} // namespace nash

#endif
