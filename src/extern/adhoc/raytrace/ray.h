#ifndef RAY_H
#define RAY_H

#include "utility/math.h"

namespace nash {
class Ray {
public:
  Vector3f pos, dir;
  Ray(const Vector3f &pos, const Vector3f &dir);
  void step();
};
} // namespace nash

#endif
