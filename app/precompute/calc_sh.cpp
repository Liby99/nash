#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  if (argc < 6) {
    std::cout << "Please specify l, m, x, y and z" << std::endl;
    return -1;
  }

  int l = std::atoi(argv[1]);
  int m = std::atoi(argv[2]);
  float x = std::atof(argv[3]);
  float y = std::atof(argv[4]);
  float z = std::atof(argv[5]);

  Vector3f dir(x, y, z);
  dir.normalize();

  std::cout << "Calculating sh with l = " << l << ", m = " << m << " in direction <" << dir.x()
            << ", " << dir.y() << ", " << dir.z() << ">" << std::endl;
  Vector2f thetaPhi = Math::normalCartToPolar(dir);
  float theta = thetaPhi[0], phi = thetaPhi[1];
  std::cout << "Theta = " << theta << ", Phi = " << phi << std::endl;
  std::cout << "Y_" << l << "^" << m << "(" << theta << ", " << phi
            << ") = " << SH::y(l, m, theta, phi) << std::endl;
}