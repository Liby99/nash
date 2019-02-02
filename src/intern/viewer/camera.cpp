#include "viewer/camera.h"

using namespace nash;

Camera::Camera() :
  position(0, 0, -1), center(0, 0, 0), up(0, 1, 0), width(1280), height(720),
  nearPlane(0.1), farPlane(100), aspectRatio(1.7777778), fovy(45) {
  
}
