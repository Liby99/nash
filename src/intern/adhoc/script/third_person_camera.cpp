#include "adhoc/script/third_person_camera.h"

using namespace nash;

ThirdPersonCamera::ThirdPersonCamera() : Script<Camera>("third-person-camera"),
  azimuth(0), incline(0), distance(3) { }

void ThirdPersonCamera::update() {

  // We first get the keyboard input to move the target of the camera
  Vector3f vel = Vector3f(0, 0, 0);
  if (context->getKey(' ')) {
    vel.y() += MOVE_SPEED;
  }
  if (context->getKey('x')) {
    vel.y() -= MOVE_SPEED;
  }
  if (context->getKey('w')) {
    vel.z() -= cos(azimuth) * MOVE_SPEED;
    vel.x() -= sin(azimuth) * MOVE_SPEED;
  }
  if (context->getKey('s')) {
    vel.z() += cos(azimuth) * MOVE_SPEED;
    vel.x() += sin(azimuth) * MOVE_SPEED;
  }
  if (context->getKey('a')) {
    vel.x() -= cos(azimuth) * MOVE_SPEED;
    vel.z() += sin(azimuth) * MOVE_SPEED;
  }
  if (context->getKey('d')) {
    vel.x() += cos(azimuth) * MOVE_SPEED;
    vel.z() -= sin(azimuth) * MOVE_SPEED;
  }
  target->target += vel;

  // Then we get the mouse input to change azimuth, incline and distance when is dragging
  if (context->getMouseLeft()) {
    Vector2i curRel = context->getCursorMovement();
    azimuth -= curRel.x() * ROTATE_SPEED;
    incline = fmaxf(-PI / 2 + 0.01f, fminf(PI / 2 - 0.01f, incline + curRel.y() * ROTATE_SPEED));
  }

  // Get the scroll event
  distance = fmaxf(0.01f, distance - context->getScrollMovement().y() * SCROLL_SPEED);

  // Then we calculate the position based on center and azimuth, incline and distance
  float x = target->target.x() + sin(azimuth) * cos(incline) * distance;
  float y = target->target.y() + sin(incline) * distance;
  float z = target->target.z() + cos(azimuth) * cos(incline) * distance;
  target->position = Vector3f(x, y, z);
}
