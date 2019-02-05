#ifndef SH_SPHERE_H
#define SH_SPHERE_H

#include "object/sphere.h"
#include "sh/sh.h"

namespace nash {
  class SHSphere : public Sphere {
  public:
    SHSphere(int l, int m);
    int getL();
    int getM();
  private:
    int l, m;
    void updatePositions();
  };
}

#endif
