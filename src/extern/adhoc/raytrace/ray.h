#ifndef RAY_H
#define RAY_H

using namespace {
  class Ray {
  public:
    Vector3f pos, dir;
    Ray(const Vector3f & pos, const Vector3f & dir);
    void step();
  };
}

#endif
