#ifndef THIRD_PERSON_CAMERA_H
#define THIRD_PERSON_CAMERA_H

#include "utility/script.h"
#include "viewer/camera.h"

namespace nash {
  class ThirdPersonCamera : public Script<Camera> {
  public:
    static constexpr float MOVE_SPEED = 0.03f;
    static constexpr float SCROLL_SPEED = 0.01f;
    static constexpr float ROTATE_SPEED = 0.005f;

    ThirdPersonCamera();
    void update();
  private:
    float azimuth, incline, distance;
  };
}

#endif
