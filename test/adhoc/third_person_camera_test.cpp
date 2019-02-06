#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.camera.setController(camCtrl);

  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());

  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();
  nanogui::shutdown();
}
