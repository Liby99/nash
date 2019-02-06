#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <stdexcept>
#include "viewer/context.h"
#include "utility/transform.h"
#include "utility/shader.h"

namespace nash {
  class Script;

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
    void show();
    void hide();
    void setHidden(bool h);
    bool isHidden();

    // Scripting
    void attachScript(Script & script);
    Script & getScript(std::string & name);
    void removeScript(std::string & name);

    // Object Life Cycle pipeline.
    virtual void start();
    virtual void update();
    virtual void render();

    // Base wrapper which could not be changed.
    void startWrapper(Context & context);
    void updateWrapper(Context & context, Matrix4f & world);
    void renderWrapper(Context & context, Matrix4f & viewPersp);

  protected:
    bool active, hidden;
    Context * context;
    Shader * shader;
    Object * parent;
    std::vector<Object *> children;
    std::vector<Script *> scripts;
  };
}

#endif
