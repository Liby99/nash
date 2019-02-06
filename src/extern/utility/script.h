#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include "object/object.h"
#include "utility/math.h"

namespace nash {
  class Script {
  public:
    const std::string name;
    Script(const std::string & name);
    void bind(Object * obj);
    virtual void start();
    virtual void update();
    virtual void render();
  protected:
    Object * object;
  };
}

#endif
