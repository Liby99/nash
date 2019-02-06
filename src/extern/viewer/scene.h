#ifndef SCENE_H
#define SCENE_H

#include "viewer/context.h"
#include "viewer/camera.h"
#include "object/object.h"

namespace nash {
  class Scene {
  public:
    Camera camera;
    Object root;

    Scene();
    
    void setSize(int width, int height);
    
    void addObject(Object & object);
    
    void start(Context & context);
    void update(Context & context);
    void render(Context & context);
  private:
  };
}

#endif
