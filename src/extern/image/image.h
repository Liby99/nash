#ifndef IMAGE_H
#define IMAGE_H

#include "utility/math.h"
#include "utility/path.h"
#include <string>

namespace nash {
  class Image {
  public:
    int width, height, numChannels;
    unsigned char *data;

    Image(const std::string &filename);
    ~Image();

    Vector4u getColor(int i, int j) const;
  };
}

#endif
