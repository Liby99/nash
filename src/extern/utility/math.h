#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <Eigen/Dense>

#define PI 3.14159265358979323846

using namespace Eigen;

typedef Eigen::Matrix<uint32_t, 4, 1> Vector4u;
typedef Eigen::Matrix<uint32_t, 3, 1> Vector3u;
typedef Eigen::Matrix<uint32_t, 2, 1> Vector2u;
typedef Eigen::Matrix<uint32_t, Eigen::Dynamic, Eigen::Dynamic> MatrixXu;

namespace nash {
  class Math {
  public:
    static Vector2f normalCartToPolar(const Vector3f & pos);
  };
}

#endif
