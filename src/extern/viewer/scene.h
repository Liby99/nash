#ifndef SCENE_H
#define SCENE_H

#include "viewer/camera.h"
#include "object/object.h"

namespace nash {
  class Scene {
  public:
    Camera camera;
    Object root;

    Scene();
    void setSize(int width, int height);
    void start();
    void update();
    void render();
  private:
  };
}

#endif
