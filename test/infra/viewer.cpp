/**
 * Test to see if a viewer could be loaded
 */

#include <nash/nash.h>

using namespace nash;

int main() {
  Nash::init();

  Scene scene;
  Viewer viewer(1280, 720, "Viewer test", scene);
  viewer.start();

  Nash::shutdown();
}
