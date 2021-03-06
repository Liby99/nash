#ifndef SH_H
#define SH_H

#include "utility/math.h"

namespace nash {
  class SH {
  public:
    static float y(int l, int m, float theta, float phi);
    static float p(int l, int m, float x);
    static float k(int l, int m);
    static int getCoefIndex(int l, int m);
    static int getNumCoefs(int numDegree);

  private:
    static int factorial(unsigned int i);
  };
}

#endif
