#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include "viewer/context.h"
#include "utility/math.h"

namespace nash {
  template<typename T>
  class Script {
  public:
    const std::string name;

    Script(const std::string & name) : name(name) {
      // Do nothing
    }

    void setContext(Context & ctx) {
      context = &ctx;
    }

    void bind(T & tar) {
      target = &tar;
    }

    virtual void start() {
      // Do nothing
    }

    virtual void update() {
      // Do nothing
    }
    
    virtual void preRender() {
      // Do nothing
    }
    
    virtual void postRender() {
      // Do nothing
    }
  protected:
    Context * context;
    T * target;
  };
}

#endif
