#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();
  Scene scene;
  scene.camera.position << 3, 3, 3;

  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());
  Toggle cubeToggle("toggle", true);
  cube.attachScript(cubeToggle);

  Sphere sphere;
  sphere.setParent(scene.root);
  sphere.setShader(Shader::get());
  Toggle sphereToggle("toggle", false);
  sphere.attachScript(sphereToggle);

  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();
  nanogui::shutdown();
}
