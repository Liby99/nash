#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>

namespace nash {
  class Object;

  class Script {
  public:
    const std::string name;
    Script(const std::string & name);
    void bind(Object * obj);
    virtual void start();
    virtual void update();
  protected:
    Object * object;
  };
}

#endif
