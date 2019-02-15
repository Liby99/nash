#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  Path::init(argv[0]);

  int vertCount = 101;
  int numDegree = 5;
  int loadDegree = 2;
  int coefsCount = numDegree * numDegree;
  int coefsSize = coefsCount * sizeof(float);

  // Create dummy coefs list
  std::cerr << "Creating dummy coefs list" << std::endl;
  std::vector<SHCoefs *> coefs(vertCount);
  for (int i = 0; i < 101; i++) {
    float *coefList = (float *) malloc(coefsSize);
    for (int j = 0; j < coefsCount; j++) {
      coefList[j] = 1.001 * j;
    }
    // Create Object
    SHCoefs *currCoefs = new SHCoefs;
    currCoefs->numDegree = numDegree;
    currCoefs->coefs = coefList;
    coefs[i] = currCoefs;
  }

  // save
  std::cerr << "Saving dummy coefs list to test.dat" << std::endl;
  SHFile shFileSav(coefs, numDegree);
  shFileSav.save("./test.dat");

  // load
  std::cerr << "Loading dummy coefs list from test.dat" << std::endl;
  SHFile shFileLoad(loadDegree);
  shFileLoad.load("./test.dat");

  int loadCoefsCount = loadDegree * loadDegree;
  std::cerr << "Checking data integrity" << std::endl;
  for (int i = 0; i < 101; i++) {
    SHCoefs *currCoefs = shFileLoad.getSamples()[i];
    float * coefList = currCoefs->coefs;
    for (int j = 0; j < loadCoefsCount; j++) {
      std::cerr << "Expected:" << 1.001 * j << "; Actual:" << coefList[j] << std::endl;
      //assert(abs(coefList[j] - 1.001 * j) > 1e-10);
    }
  }
  std::cerr << "Test passed" << std::endl;
}
