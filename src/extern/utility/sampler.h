#ifndef SAMPLER_H
#define SAMPLER_H

#include "utility/math.h"
#include <vector>

namespace nash {
  class Sampler {
  public:
    static void sampleSphere(std::vector<Vector2f> &samples);
    static Vector2f sampleSphere();
    static void sampleHemiSphere(std::vector<Vector2f> &samples);
    static Vector2f sampleHemiSphere();
  };
}

#endif
