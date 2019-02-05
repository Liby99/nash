#ifndef CUBE_H
#define CUBE_H

#include "object/object.h"

namespace nash {
  class Cube : public Object {
  public:
    Cube();
    virtual void render();
  protected:
    nanogui::MatrixXu indices;
    MatrixXf positions;
    MatrixXf normals;
  };
}

#endif
