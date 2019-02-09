#include "object/mesh.h"

using namespace nash;

Mesh::Mesh() : Object() { Object::setShader(Shader::get()); }

void Mesh::render() {
  shader->uploadIndices(indices);
  shader->uploadAttr("position", positions);
  shader->uploadAttr("normal", normals);
  shader->uploadAttr("texCoord", texCoords);
  shader->drawIndexed(GL_TRIANGLES, 0, indices.cols());
}
