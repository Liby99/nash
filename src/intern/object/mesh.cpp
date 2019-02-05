#include "object/mesh.h"

using namespace nash;

Mesh::Mesh() : Object() {
  // Do nothing
}

void Mesh::render() {
  shader->uploadIndices(indices);
  shader->uploadAttr("position", positions);
  shader->uploadAttr("normal", normals);
  shader->drawIndexed(GL_TRIANGLES, 0, indices.cols());
}
