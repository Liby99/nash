#ifndef ROTATOR_H
#define ROTATOR_H

#include "object/object.h"
#include "utility/script.h"

namespace nash {
  class Rotator : public Script<Object> {
  public:
    float speed;
    Vector3f axis;
    Rotator(const std::string &name);
    Rotator(const std::string &name, float speed, Vector3f axis);
    virtual void update();
  };
}

#endif
