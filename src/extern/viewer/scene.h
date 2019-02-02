#ifndef SCENE_H
#define SCENE_H

#include "object/Object.h"

namespace nash {
  class Scene {
  public:
    Camera camera;
    Object root;

    Scene();
    void update();
    void render();
  private:
  };
}

#endif
