#include <nash/nash.h>
#include <chrono>

using namespace nash;

const int DEFAULT_NUM_DEGREE = 5;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  // Check if there's filename specified
  if (argc < 2) {
    std::cout << "Please specify the file name" << std::endl;
    std::cout << "Usage: ./obj_coef_calculator [-d <num_degree>] [-p] <filename>.obj" << std::endl;
    return -1;
  }

  // Parse the command line arguments
  std::string filename = std::string(argv[argc - 1]);
  int numDegree = DEFAULT_NUM_DEGREE;
  bool printOnly = false;
  for (int i = 1; i < argc - 1; i++) {
    std::string str = std::string(argv[i]);
    if (str == "-d") {
      std::string degreeStr = std::string(argv[++i]);
      numDegree = std::stoi(degreeStr);
      if (numDegree <= 0) {
        std::cout << "The option <num_degree> must be greater than 0" << std::endl;
        return -1;
      }
    } else if (str == "-p") {
      printOnly = true;
    }
  }

  // Load the file and get the meshes
  std::cout << "Loading obj file " << filename << std::endl;
  AssimpObject obj(filename);
  auto meshes = obj.getMeshes();

  // Save a coef file for each meshes
  std::cout << "Start calculating sh coefs for Object " << filename << std::endl;
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < meshes.size(); i++) {
    AssimpMesh &mesh = *(meshes[i]);
    std::cout << "- Calculating Mesh: " << mesh.getName() << "..." << std::endl;
    MeshSHCalculator calc(mesh, numDegree);
    SHFile file(calc.getCoefsList(), numDegree);
    if (printOnly) {
      file.print();
    } else {
      std::string saveFilename = "./" + mesh.getName() + ".obj.coef";
      std::cout << "- Saving coef file " << saveFilename << std::endl;
      file.save(saveFilename);
    }
  }
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Total time elapsed: " << elapsed.count() / 1000 << "s" << std::endl;

  Nash::shutdown();
}