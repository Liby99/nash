/**
 * Similar test to `cube_rotator.cpp`. We are rendering a `SHSphere` instead of
 * a cube here.
 */

#include <nash/nash.h>

using namespace nash;

int main() {
  Nash::init();

  Scene scene;
  scene.camera.position << 1, 1, 1;

  SHSphere sphere(2, 2);
  Rotator rotator("rotator");
  sphere.attachScript(rotator);
  scene.addObject(sphere);

  Viewer viewer(1280, 720, "Spherical Harmonics Sphere Viewer", scene);
  viewer.start();

  Nash::shutdown();
}
