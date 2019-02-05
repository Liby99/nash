#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();
  Scene scene;
  scene.camera.position << 2, 2, 2;
  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());
  Viewer viewer(1280, 720, "Viewer test", scene);
  viewer.start();
  nanogui::shutdown();
}
