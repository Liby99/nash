#ifndef SH_SPHERE_H
#define SH_SPHERE_H

#include "adhoc/sh/sh.h"
#include "adhoc/sh/sh_coefs.h"
#include "object/primitive/sphere.h"
#include <stdio.h>

namespace nash {
  class SHSphere : public Sphere {
  public:
    SHSphere(int l, int m);
    SHSphere(const SHCoefs &coefs);
    virtual void render();

  private:
    SHCoefs coefs;
    MatrixXf values;
    void initShader();
    void updatePositions();
  };
}

#endif
