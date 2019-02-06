#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();

  Scene scene;
  scene.camera.position << 3, 3, 3;

  Sphere sphere(2); // Initialize low poly sphere to see its rotation
  sphere.setParent(scene.root);
  sphere.setShader(Shader::get());
  Rotator rotator("rotator");
  sphere.attachScript(rotator);

  Viewer viewer(1280, 720, "Rotating Sphere Viewer test", scene);
  viewer.start();
  nanogui::shutdown();
}
