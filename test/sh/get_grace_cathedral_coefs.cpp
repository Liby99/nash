#include <nash/nash.h>

using namespace nash;

const std::string directory = "./image/cubemap/gracecathedral/";

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Image right(directory + "posx.jpg");
  Image left(directory + "negx.jpg");
  Image top(directory + "posy.jpg");
  Image down(directory + "negy.jpg");
  Image front(directory + "posz.jpg");
  Image back(directory + "negz.jpg");
  CubeMap cubeMap(top, down, left, right, front, back);

  SkyBoxSHCalculator calc(cubeMap, 3);
  const std::vector<SHCoefs *> &list = calc.getCoefsList();

  std::cout << "Red: " << list[0]->toString() << std::endl;
  std::cout << "Green: " << list[1]->toString() << std::endl;
  std::cout << "Blue: " << list[2]->toString() << std::endl;

  Nash::shutdown();
}