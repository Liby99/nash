/**
 * Just a simple test of whether the system can render a simple cube on the
 * screen
 */

#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  scene.getCamera().position << 3, 3, 3;
  Cube cube;
  scene.addObject(cube);
  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();

  Nash::shutdown();
}
