#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();
  Scene scene;
  Viewer viewer(1280, 720, "Viewer test", scene);
  viewer.start();
  nanogui::shutdown();
}
