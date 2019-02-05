#include "utility/transformation.h"

using namespace nash;

Transformation::Transformation() :
  world(Matrix4f::Identity()),
  rotation(Quaternionf::Identity()),
  position(Vector3f::Zero()),
  scale(Vector3f::Identity()) {
  // Do Nothing
}

Matrix4f Transformation::getTransform() {
  Matrix4f local = Matrix4f::Zero();
  local.col(3) << position.x(), position.y(), position.z(), 1;
  local.block(0, 0, 2, 2) = rotation.normalized().toRotationMatrix();
  local.block(0, 0, 2, 2) *= Scaling(scale);
  return local * world;
}
