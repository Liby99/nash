#ifndef SH_COEFS_H
#define SH_COEFS_H

#include "adhoc/sh/sh.h"

namespace nash {
  class SHCoefs {
  public:
    int numDegree;
    float *coefs;

    SHCoefs();
    SHCoefs(int numDegree);
  };
}

#endif