#ifndef MESH_H
#define MESH_H

#include "object/object.h"

namespace nash {
  class Mesh : public Object {
  public:
    Mesh();
    virtual void render();

  protected:
    MatrixXu indices;
    MatrixXf positions;
    MatrixXf normals;
  };
}

#endif
