#ifndef SH_COLOR_H
#define SH_COLOR_H

#include "sh_coefs.h"

namespace nash {
  class SHColor {
  public:
    SHCoefs red, green, blue;
    SHColor(const SHCoefs &red, const SHCoefs &green, const SHCoefs &blue);
  };
}

#endif