#include "adhoc/script/rotator.h"

using namespace nash;

Rotator::Rotator(const std::string &name) : Rotator(name, 0.01, Vector3f(0, 1, 0)) {}

Rotator::Rotator(const std::string &name, float speed, Vector3f axis)
    : Script(name), counter(0), speed(speed), axis(axis) {}

void Rotator::update() { target->transform.rotation = AngleAxisf((++counter) * speed, axis); }
