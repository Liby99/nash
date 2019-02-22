#include "adhoc/script/rotator.h"

using namespace nash;

Rotator::Rotator(const std::string &name) : Rotator(name, 1, Vector3f(0, 1, 0)) {}

Rotator::Rotator(const std::string &name, float speed, Vector3f axis)
    : Script(name), speed(speed), axis(axis) {}

void Rotator::update() {
  double time = context->getElapsedTime();
  target->transform.rotation = AngleAxisf(time * speed, axis);
}
