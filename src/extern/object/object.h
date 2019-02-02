#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "utility/transform.h"

namespace nash {
  class Object {
  public:
    Transform transform;

    Object();

    // Scene tree
    Object & getParent();
    void setParent(Object * p);
    void removeFromParent();
    std::vector<Object *> & getChildren();
    Object & getChild(int i);

    // Shader spec
    Shader & getShader();
    void setShader(Shader & shader);

    // Activation
    void setActive(bool active);
    bool isActive();

    // Object Life Cycle pipeline. 
    virtual void start();
    virtual void update();
    virtual void render();

    // Base wrapper which could not be changed.
    void startWrapper();
    void updateWrapper();
    void renderWrapper();

  private:
    bool active;
    Shader * shader;
    Object * parent;
    std::vector<Object *> children;
  };
}

#endif
