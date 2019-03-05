#include <nash/nash.h>

using namespace nash;

const std::string directory = "./image/cubemap/room/";

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Image right(Path::getAbsolutePathTo(directory + "posx.jpg"));
  Image left(Path::getAbsolutePathTo(directory + "negx.jpg"));
  Image top(Path::getAbsolutePathTo(directory + "posy.jpg"));
  Image down(Path::getAbsolutePathTo(directory + "negy.jpg"));
  Image front(Path::getAbsolutePathTo(directory + "posz.jpg"));
  Image back(Path::getAbsolutePathTo(directory + "negz.jpg"));
  CubeMap cubeMap(top, down, left, right, front, back);

  SkyBoxSHCalculator calc(cubeMap, 3, 10);
  const std::vector<SHCoefs *> &list = calc.getCoefsList();

  std::cout << "Red: " << list[0]->toString() << std::endl;
  std::cout << "Green: " << list[1]->toString() << std::endl;
  std::cout << "Blue: " << list[2]->toString() << std::endl;

  Nash::shutdown();
}