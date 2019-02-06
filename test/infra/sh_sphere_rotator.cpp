#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();

  Scene scene;
  scene.camera.position << 1, 1, 1;

  SHSphere sphere(2, 2);
  sphere.setParent(scene.root);
  sphere.setShader(Shader::get());
  Rotator rotator("rotator");
  sphere.attachScript(rotator);

  Viewer viewer(1280, 720, "Spherical Harmonics Sphere Viewer", scene);
  viewer.start();
  nanogui::shutdown();
}