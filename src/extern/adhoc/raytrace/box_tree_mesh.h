#ifndef BOX_TREE_MESH_H
#define BOX_TREE_MESH_H

#include <nash/nash.h>
#include <object/mesh.h>

namespace nash {
  class BoxTreeNode;
  class BoxTreeMesh {
  public:
    BoxTreeMesh(const Mesh &mesh);
    bool intersect(const Ray &ray, Intersection &intersection);
    ~BoxTreeMesh();

    const Mesh &getMesh() const;

    int leafSize = 1;

  private:
    void partition();
    const Mesh &mesh;
    BoxTreeNode *root;
  };
}

#endif
