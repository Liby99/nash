#ifndef SH_SPHERE_H
#define SH_SPHERE_H

#include "adhoc/sh/sh.h"
#include "adhoc/sh/sh_coefs.h"
#include "object/primitive/sphere.h"
#include <stdio.h>

namespace nash {
  class SHSphere : public Sphere {
  public:
    SHSphere(int l, int m, int subdivision = 5);
    SHSphere(const SHCoefs &coefs, int subdivision = 5);
    virtual void render();

  private:
    const SHCoefs *coefs;
    MatrixXf values;
    void initShader();
    void updatePositions();
  };
}

#endif
