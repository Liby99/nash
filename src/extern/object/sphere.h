#ifndef SPHERE_H
#define SPHERE_H

#include "object/mesh.h"

namespace nash {
  class Sphere : public Mesh {
  public:
    static const int SUBDIVISION = 3;
    Sphere();
  private:
    typedef std::vector<Vector3f> Vertices;
    typedef std::vector<Vector3u> Triangles;
    void generateMesh();
    void subdivide(Vertices & vertices, Triangles & triangles, int step);
  };
}

#endif
