/**
 * Just a simple test of whether the system can render a simple cube on the screen
 */

#include <nash/nash.h>

using namespace nash;

int main() {
  Nash::init();

  Scene scene;
  scene.camera.position << 3, 3, 3;
  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());
  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();

  Nash::shutdown();
}
