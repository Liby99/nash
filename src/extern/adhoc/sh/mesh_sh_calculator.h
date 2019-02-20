#ifndef MESH_SH_CALCULATOR_H
#define MESH_SH_CALCULATOR_H

#include "adhoc/sh/sh_coefs.h"
#include "object/mesh.h"

namespace nash {
  class MeshSHCalculator {
  public:
    static const int SAMPLE_COUNT;
    int numDegree;
    MeshSHCalculator(const Mesh &mesh, int numDegree);
    ~MeshSHCalculator();
    const std::vector<SHCoefs *> &getCoefsList();

  private:
    const Mesh &mesh;
    std::vector<SHCoefs *> coefsList;
  };
}

#endif