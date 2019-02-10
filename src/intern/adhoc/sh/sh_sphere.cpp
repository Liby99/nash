#include "adhoc/sh/sh_sphere.h"

using namespace nash;

SHSphere::SHSphere(int l, int m) : Sphere(), l(l), m(m) {
  if (abs(m) > l) {
    std::string ms = std::to_string(m), ls = std::to_string(l);
    throw std::invalid_argument("expected |m| < l, but found m = " + ms + ", l = " + ls);
  }
  updatePositions();
  setShader(Shader::get("./shader/sh_sphere"));
}

int SHSphere::getL() { return l; }

int SHSphere::getM() { return m; }

void SHSphere::render() {
  shader->uploadAttr("shCoef", coefs);
  Sphere::render();
}

void SHSphere::updatePositions() {

  // Generate coefficients
  coefs = MatrixXf(1, positions.cols());

  // First loop through all positions and set the radius from center to be SH::y
  for (int i = 0; i < positions.cols(); i++) {
    Vector2f thetaPhi = Math::normalCartToPolar(positions.col(i));
    float theta = thetaPhi.x(), phi = thetaPhi.y();
    float sh = SH::y(l, m, theta, phi);
    positions.col(i) *= abs(sh);
    coefs.col(i) << sh;

    // Temporarily set normal to 0
    normals.col(i) = Vector3f::Zero();
  }

  // Then loop through all the surfaces to add up the normals to each vertex
  for (int i = 0; i < indices.cols(); i++) {
    uint32_t i1 = indices.col(i).x(), i2 = indices.col(i).y(), i3 = indices.col(i).z();
    Vector3f v1 = positions.col(i1), v2 = positions.col(i2), v3 = positions.col(i3);
    Vector3f surfaceNormal = (v3 - v1).cross(v2 - v1).normalized();
    normals.col(i1) += surfaceNormal;
    normals.col(i2) += surfaceNormal;
    normals.col(i3) += surfaceNormal;
  }

  // Finally normalize all the normals
  for (int i = 0; i < normals.cols(); i++) {
    normals.col(i) = normals.col(i).normalized();
  }
}
