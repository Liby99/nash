#ifndef CAMERA_H
#define CAMERA_H

#include "utility/math.h"

using namespace Eigen;

namespace nash {
  class Camera {
  public:
    Vector3f position;
    Vector3f target;
    Vector3f up;

    int width, height;
    float zNear, zFar;
    float aspect;
    float fovy;

    Camera();
    void setSize(int width, int height);
    Matrix4f getViewPerspective();
  protected:
    Matrix4f getView();
    Matrix4f getPerspective();
  };
}

#endif
