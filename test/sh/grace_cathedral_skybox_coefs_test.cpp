#include "helpers/looper.hpp"
#include <nash/nash.h>

using namespace nash;

const std::string directory = "./image/cubemap/gracecathedral/";

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  Image right(directory + "posx.jpg");
  Image left(directory + "negx.jpg");
  Image top(directory + "posy.jpg");
  Image down(directory + "negy.jpg");
  Image front(directory + "posz.jpg");
  Image back(directory + "negz.jpg");
  CubeMap cubeMap(top, down, left, right, front, back);
  SkyBox skybox(cubeMap);

  scene.addObject(skybox);

  SkyBoxSHCalculator calc(cubeMap, 8);
  const std::vector<SHCoefs *> &list = calc.getCoefsList();

  std::cout << "Red: " << list[0]->toString() << std::endl;
  std::cout << "Green: " << list[1]->toString() << std::endl;
  std::cout << "Blue: " << list[2]->toString() << std::endl;

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