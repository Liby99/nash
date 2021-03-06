#include "helper/looper.hpp"
#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  Image right(Path::getAbsolutePathTo("./image/cubemap/room/posx.jpg"));
  Image left(Path::getAbsolutePathTo("./image/cubemap/room/negx.jpg"));
  Image top(Path::getAbsolutePathTo("./image/cubemap/room/posy.jpg"));
  Image down(Path::getAbsolutePathTo("./image/cubemap/room/negy.jpg"));
  Image front(Path::getAbsolutePathTo("./image/cubemap/room/posz.jpg"));
  Image back(Path::getAbsolutePathTo("./image/cubemap/room/negz.jpg"));
  CubeMap cubeMap(top, down, left, right, front, back);

  SkyBox skybox(cubeMap);
  scene.addObject(skybox);

  SkyBoxSHCalculator calc(cubeMap, 8, 10);
  auto list = calc.getCoefsList();
  SHSphere redSphere(*list[0]);
  SHSphere greenSphere(*list[1]);
  SHSphere blueSphere(*list[2]);
  Looper redLooper("red-looper", 0, 3);
  Looper greenLooper("green-looper", 1, 3);
  Looper blueLooper("blue-looper", 2, 3);
  redSphere.attachScript(redLooper);
  greenSphere.attachScript(greenLooper);
  blueSphere.attachScript(blueLooper);

  scene.addObject(redSphere);
  scene.addObject(blueSphere);
  scene.addObject(greenSphere);

  Viewer viewer(1280, 720, "Skybox Coef Viewer", scene);
  viewer.start();

  Nash::shutdown();
}