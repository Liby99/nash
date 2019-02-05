#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <stdexcept>
#include "utility/transform.h"
#include "utility/shader.h"
#include "utility/script.h"

namespace nash {
  class Object {
  public:
    nash::Transform transform;

    Object();

    // Scene tree
    bool hasParent();
    Object & getParent();
    void setParent(Object & p);
    void removeFromParent();
    std::vector<Object *> & getChildren();
    Object & getChild(int i);

    // Shader spec
    bool hasShader();
    Shader & getShader();
    void setShader(Shader & shader);

    // Activation
    void activate();
    void deactivate();
    void setActive(bool active);
    bool isActive();

    // Scripting
    void attachScript(Script & script);
    Script & getScript(std::string & name);
    void removeScript(std::string & name);

    // Object Life Cycle pipeline.
    virtual void start();
    virtual void update();
    virtual void render();

    // Base wrapper which could not be changed.
    void startWrapper();
    void updateWrapper(Matrix4f & world);
    void renderWrapper(Matrix4f & viewPersp);

  protected:
    bool active;
    Shader * shader;
    Object * parent;
    std::vector<Object *> children;
    std::vector<Script *> scripts;
  };
}

#endif
