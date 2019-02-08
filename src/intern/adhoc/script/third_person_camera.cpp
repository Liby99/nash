#include "adhoc/script/third_person_camera.h"

using namespace nash;

ThirdPersonCamera::ThirdPersonCamera()
    : Script<Camera>("third-person-camera"), azimuth(0), incline(0), distance(3) {}

void ThirdPersonCamera::update() {

  // We first get the keyboard input to move the target of the camera
  Vector3f vel = Vector3f(0, 0, 0);
  if (context->getKey(' '))
    vel.y() += 1;
  if (context->getKey('x'))
    vel.y() -= 1;
  if (context->getKey('w'))
    vel -= Vector3f(sin(azimuth), 0, cos(azimuth));
  if (context->getKey('s'))
    vel += Vector3f(sin(azimuth), 0, cos(azimuth));
  if (context->getKey('a'))
    vel += Vector3f(-cos(azimuth), 0, sin(azimuth));
  if (context->getKey('d'))
    vel += Vector3f(cos(azimuth), 0, -sin(azimuth));
  target->target += vel.normalized() * MOVE_SPEED;

  // Then we get the mouse input to change azimuth, incline and distance when is
  // dragging
  if (context->getMouseLeft()) {
    Vector2i curRel = context->getCursorMovement();
    azimuth -= curRel.x() * ROTATE_SPEED;
    incline = fmaxf(-PI / 2 + 0.01f, fminf(PI / 2 - 0.01f, incline + curRel.y() * ROTATE_SPEED));
  }

  // Get the scroll event
  distance = fmaxf(0.01f, distance - context->getScrollMovement().y() * SCROLL_SPEED);

  // Then we calculate the position based on center and azimuth, incline and
  // distance
  float x = target->target.x() + sin(azimuth) * cos(incline) * distance;
  float y = target->target.y() + sin(incline) * distance;
  float z = target->target.z() + cos(azimuth) * cos(incline) * distance;
  target->position = Vector3f(x, y, z);
}
