#ifndef SH_SPHERE_H
#define SH_SPHERE_H

#include "adhoc/sh/sh.h"
#include "object/primitive/sphere.h"
#include <stdio.h>

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
} // namespace nash

#endif
