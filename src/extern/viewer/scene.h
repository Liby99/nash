#ifndef SCENE_H
#define SCENE_H

#include "object/object.h"

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
