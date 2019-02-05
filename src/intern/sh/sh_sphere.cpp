#include "sh/sh_sphere.h"

using namespace nash;

SHSphere::SHSphere(int l, int m) : Sphere(), l(l), m(m) {
  // if (abs(m) > l) {
  //   throw std::invalid_argument("The absolute value of m should be less than l");
  // }
  updatePositions();
}

int SHSphere::getL() {
  return l;
}

int SHSphere::getM() {
  return m;
}

void SHSphere::updatePositions() {
  for (int i = 0; i < positions.cols(); i++) {
    Vector2f thetaPhi = Math::normalCartToPolar(positions.col(i));
    float sh = SH::y(l, m, thetaPhi.x(), thetaPhi.y());
    positions.col(i) *= abs(sh);
  }
}
