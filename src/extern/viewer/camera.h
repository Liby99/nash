#ifndef CAMERA_H
#define CAMERA_H

#include "utility/math.h"

using namespace Eigen;

namespace nash {
  class Camera {
  public:
    Vector3f position;
    Vector3f center;
    Vector3f up;

    int width, height;
    float nearPlane, farPlane;
    float aspectRatio;
    float fovy;

    Camera();
  };
}

#endif
