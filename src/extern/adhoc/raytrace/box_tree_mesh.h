#ifndef BOX_TREE_MESH_H
#define BOX_TREE_MESH_H

#include "object/mesh.h"
#include "adhoc/raytrace/ray.h"
#include "adhoc/raytrace/intersection.h"

namespace nash {
  class BoxTreeMesh {
  public:
    BoxTreeMesh(const Mesh & mesh);
    bool intersect(const Ray & ray, Intersection & intersection);
  };
}

#endif
