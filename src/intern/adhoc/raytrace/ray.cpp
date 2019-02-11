#include "adhoc/raytrace/ray.h"

using namespace nash;

Ray::Ray(const Vector3f &pos, const Vector3f &dir) :
  pos(pos),
  dir(dir.normalized()){
    Vector3f normDir = dir.normalized();
    invDir = Vector3f(normDir[0], normDir[1], normDir[2]);
}

void Ray::step() { pos += dir * 0.0001f; }
