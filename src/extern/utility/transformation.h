#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "utility/math.h"

namespace nash {
  class Transformation {
  public:
    Matrix4f world;
    Quaternionf rotation;
    Vector3f position;
    Vector3f scale;

    Transformation();
    Matrix4f getTransform();
  };
}

#endif
