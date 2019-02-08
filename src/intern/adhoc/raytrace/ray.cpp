#include "adhoc/raytrace/ray.h"

using namespace nash;

Ray::Ray(const Vector3f &pos, const Vector3f &dir) : pos(pos), dir(dir.normalized()) {}

void Ray::step() { pos += dir * 0.0001f; }
