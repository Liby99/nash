#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "utility/math.h"

namespace nash {
  class Transform {
  public:
    Quaternionf rotation;
    Vector3f position;
    Vector3f scale;
  };
}

#endif
