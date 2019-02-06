#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();
  Scene scene;
  scene.camera.position << 3, 3, 3;
  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());

  // ========   ATTENTION   ======== //
  Rotator rotator("rotator");
  cube.attachScript(rotator);
  // ======== END ATTENTION ======== //

  Viewer viewer(1280, 720, "Rotating Cube test", scene);
  viewer.start();
  nanogui::shutdown();
}
