#include <nash/nash.h>

using namespace nash;

int main() {
  int counter = 0;
  for (int l = 0; l < 10; l++) {
    for (int m = -l; m <= l; m++) {
      int expected = counter++;
      int actual = SH::getCoefIndex(l, m);
      if (expected != actual) {
        std::cout << "Expected " << expected << ", Actual " << actual << ". FAILED" << std::endl;
        return -1;
      }
    }
  }
}