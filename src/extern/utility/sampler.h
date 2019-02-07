#ifndef SAMPLER_H
#define SAMPLER_H

#include "utility/math.h"
#include <vector>

namespace nash {
class Sampler {
public:
  static void sampleSphere(std::vector<Vector2f> &samples);
  static void sampleSphere(Vector2f &sample);
  static void sampleHemiSphere(std::vector<Vector2f> &samples);
  static void sampleHemiSphere(Vector2f &sample);
};
} // namespace nash

#endif
