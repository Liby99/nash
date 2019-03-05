#include <chrono>
#include <nash/nash.h>

using namespace nash;

const int DEFAULT_NUM_DEGREE = 5;

const int MILLI_PER_SECOND = 1000;

std::string filename;
int numDegree = DEFAULT_NUM_DEGREE;
bool printOnly = false;
bool doTiming = false;
bool silent = false;

void printHelp() {
  std::cout << "Usage: ./obj_coef_calculator [-d|--degree <num_degree>] [-p|--print] [-t|--time] "
               "[-s|--silent] [-h|--help] <filename>"
            << std::endl;
  std::cout << "This program will take in an object file, and output one or several files each "
               "representing the spherical harmonics coefficients of a mesh"
            << std::endl;
  std::cout << "Flags:" << std::endl;
  std::cout << "\t-h | --help\t\t\tPrint the Help message and terminate the program" << std::endl;
  std::cout << "\t-p | --print\t\t\tPrint out the file content instead of exporting to file"
            << std::endl;
  std::cout << "\t-t | --time\t\t\tPrint out the time elapsed when computation finished"
            << std::endl;
  std::cout << "\t-s | --silent\t\t\tDon't print anything while computing. Will override option -t "
               "(time) but will not override option -p (print)"
            << std::endl;
  std::cout << "\t-d | --degree <num_degree>\tWill contain the top <num_degree> of coefficients. "
               "The value is set to be 5 if not specified"
            << std::endl;
}

void print(const std::string &str, bool endl = true) {
  if (!silent) {
    std::cout << str;
    if (endl) {
      std::cout << std::endl;
    }
  }
}

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  // Parse the command line arguments
  bool hasFilename = false;
  for (int i = 1; i < argc; i++) {
    std::string str = std::string(argv[i]);
    if (str[0] == '-') {
      if (str == "-d" || str == "--degree") {
        std::string degreeStr = std::string(argv[++i]);
        try {
          numDegree = std::stoi(degreeStr);
          if (numDegree <= 0) {
            std::cout << "The option <num_degree> must be greater than 0" << std::endl;
            return -1;
          }
        } catch (...) {
          std::cout << "Cannot parse <num_degree>: invalid input " << degreeStr << std::endl;
          return -1;
        }
      } else if (str == "-p" || str == "--print") {
        printOnly = true;
      } else if (str == "-h" || str == "--help") {
        printHelp();
        return 0;
      } else if (str == "-t" || str == "--time") {
        doTiming = true;
      } else if (str == "-s" || str == "--silent") {
        silent = true;
      } else {
        std::cout << "Unknown flag " << str << std::endl;
        printHelp();
        return -1;
      }
    } else {
      if (!hasFilename) {
        filename = str;
        hasFilename = true;
      } else {
        std::cout << "Unknown argument " << str << std::endl;
        printHelp();
        return -1;
      }
    }
  }

  // Check if there's filename specified
  if (!hasFilename) {
    std::cout << "Please specify the file name" << std::endl;
    printHelp();
    return -1;
  }

  // Load the file and get the meshes
  print("Loading obj file " + filename + "...");
  AssimpObject obj(Path::getAbsolutePathTo(filename, true));
  auto meshes = obj.getMeshes();

  // Save a coef file for each meshes
  print("Start calculating sh coefs for Object " + filename + "...");
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < meshes.size(); i++) {
    AssimpMesh &mesh = *(meshes[i]);
    print("- Calculating Mesh: " + mesh.getName() + "...");
    MeshSHCalculator calc(mesh, numDegree);
    SHFile file(calc.getCoefsList(), numDegree);
    if (printOnly) {
      file.print();
    } else {
      std::string objName = Path::getFileName(filename), meshName = mesh.getName();
      std::string name = meshName.length() == 0 ? objName : objName + "." + meshName;
      std::string saveFilename = "./" + name + ".coef";
      print("- Saving coef file " + saveFilename + "...");
      file.save(Path::getAbsolutePathTo(saveFilename, true));
    }
  }
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  if (doTiming) {
    print("Total time elapsed: " + std::to_string(elapsed.count() / MILLI_PER_SECOND) + "s");
  }

  Nash::shutdown();
}