#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  Viewer viewer(1280, 720, "SH Environment Shadow Demo", scene);
  viewer.start();

  Nash::shutdown();
}