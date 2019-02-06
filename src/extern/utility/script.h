#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include "viewer/context.h"
#include "object/object.h"
#include "utility/math.h"

namespace nash {
  class Script {
  public:
    const std::string name;
    Script(const std::string & name);
    void setContext(Context & context);
    void bind(Object & obj);
    virtual void start();
    virtual void update();
  protected:
    Context * context;
    Object * object;
  };
}

#endif
