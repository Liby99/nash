#ifndef SH_H
#define SH_H

#import "utility/math.h"

namespace nash {
  class SH {
  public:
    static float y(int l, int m, float theta, float phi);
    static float p(int l, int m, float x);
    static float k(int l, int m);
  private:
    static int factorial(int i);
  };
}

#endif
