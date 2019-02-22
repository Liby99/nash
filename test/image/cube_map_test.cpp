#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  camCtrl.incline = PI / 4;
  scene.getCamera().setController(camCtrl);

  Cube cube;
  scene.addObject(cube);

  Image negx("./image/cubemap/room/negx.jpg");
  Image posx("./image/cubemap/room/posx.jpg");
  Image negy("./image/cubemap/room/negy.jpg");
  Image posy("./image/cubemap/room/posy.jpg");
  Image negz("./image/cubemap/room/negz.jpg");
  Image posz("./image/cubemap/room/posz.jpg");
  CubeMap cubeMap(posy, negy, negx, posx, posz, negz);
  SkyBox skybox(cubeMap);
  scene.addObject(skybox);

  Viewer viewer(1280, 720, "Skybox Test", scene);
  viewer.start();

  Nash::shutdown();
}