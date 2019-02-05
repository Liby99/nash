#include "utility/math.h"

using namespace nash;

Vector2f Math::normalCartToPolar(const Vector3f & pos) {
  return Vector2f(acos(pos.y()), atan2(pos.z(), pos.x()));
}
