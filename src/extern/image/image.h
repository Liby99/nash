#ifndef IMAGE_H
#define IMAGE_H

#include "utility/path.h"
#include <string>

namespace nash {
  class Image {
  public:
    int width, height, numChannels;
    unsigned char *data;
    Image(const std::string &filename);
    ~Image();
  };
}

#endif
