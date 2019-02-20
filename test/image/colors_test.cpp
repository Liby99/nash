#include <cassert>
#include <nash/nash.h>

using namespace nash;

bool match(float x, float y) { return std::abs(x - y) < 0.01; }

void assertColor(float r, float g, float b, float a, const Vector4u &actual) {
  bool re = match(r, actual.x() / 255.0f);
  bool ge = match(g, actual.y() / 255.0f);
  bool be = match(b, actual.z() / 255.0f);
  bool ae = match(a, actual.w() / 255.0f);
  assert(re && ge && be && ae);
  std::cout << "Passed." << std::endl;
}

int main(int argc, char *argv[]) {
  Path::init(argv[0]);

  Image right("./image/colors/posx.jpg");
  Image left("./image/colors/negx.jpg");
  Image top("./image/colors/posy.jpg");
  Image down("./image/colors/negy.jpg");
  Image front("./image/colors/posz.jpg");
  Image back("./image/colors/negz.jpg");

  std::cout << "Testing right image. Expecting Green. ";
  assertColor(0, 1, 0, 1, right.getColor(48, 26));
  std::cout << "Testing left image. Expecting Red. ";
  assertColor(1, 0, 0, 1, left.getColor(74, 4));
  std::cout << "Testing top image. Expecting Blue. ";
  assertColor(0, 0, 1, 1, top.getColor(0, 0));
  std::cout << "Testing down image. Expecting Yellow. ";
  assertColor(1, 1, 0, 1, down.getColor(20, 60));
  std::cout << "Testing front image. Expecting Cyan. ";
  assertColor(0, 1, 1, 1, front.getColor(48, 48));
  std::cout << "Testing back image. Expecting Magenta. ";
  assertColor(1, 0, 1, 1, back.getColor(60, 60));
}