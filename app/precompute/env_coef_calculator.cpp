#include <chrono>
#include <nash/nash.h>

using namespace nash;

const int DEFAULT_NUM_DEGREE = 5;

const int MILLI_PER_SECOND = 1000;

std::string filename;
std::string ext = "jpg";
int numDegree = DEFAULT_NUM_DEGREE;
bool printOnly = false;
bool doTiming = false;
bool silent = false;

void printHelp() {
  std::cout << "Usage: ./env_coef_calculator [-d|--degree <num_degree>] [-p|--print] [-t|--time] "
               "[-s|--silent] [-h|--help] [-e|--ext <extension>] <directory>"
            << std::endl;
  std::cout << "This program will take in a directory containing a set of environment map images, "
               "which will be named as `posx.jpg`, `negx.jpg`, `posy.jpg`, `negy.jpg`, `posz.jpg`, "
               "and `negz.jpg`, and output a single coefficient file containing 3 set of "
               "coefficients, each representing channel RED, GREEN and BLUE."
            << std::endl;
  std::cout << "If you don't want the file extension to be .jpg, you can use -e flag to set the "
               "file extension."
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
  std::cout << "\t-e | --ext <extension>\t\tWill set the auto image extension to <extension>. "
               "Default value is `jpg`. Some other example would be `png`, `bmp` and so on."
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
      } else if (str == "-e" || str == "--ext") {
        ext = std::string(argv[++i]);
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
    std::cout << "Please specify the env map directory" << std::endl;
    printHelp();
    return -1;
  }

  // Preprocess the path
  bool endWithSlash = filename[filename.length() - 1] == '/';
  filename = endWithSlash ? filename.substr(0, filename.length() - 1) : filename;
  std::string name = Path::getFileName(filename);

  // Load the file and get the meshes
  print("Loading env map files in directory " + filename + "/ ...");
  Image right(Path::getAbsolutePathTo(filename + "/posx." + ext, true));
  Image left(Path::getAbsolutePathTo(filename + "/negx." + ext, true));
  Image top(Path::getAbsolutePathTo(filename + "/posy." + ext, true));
  Image down(Path::getAbsolutePathTo(filename + "/negy." + ext, true));
  Image front(Path::getAbsolutePathTo(filename + "/posz." + ext, true));
  Image back(Path::getAbsolutePathTo(filename + "/negz." + ext, true));
  CubeMap cubeMap(top, down, left, right, front, back);

  // Save a coef file for each meshes
  print("Start calculating sh coefs for sky box " + name + "...");
  auto start = std::chrono::system_clock::now();

  // Start calculating
  SkyBoxSHCalculator calc(cubeMap, numDegree);
  auto list = calc.getCoefsList();
  SHFile file(calc.getCoefsList(), numDegree);
  if (printOnly) {
    file.print();
  } else {
    std::string saveFilename = "./" + name + ".env.coef";
    print("Saving coef file " + saveFilename + "...");
    file.save(Path::getAbsolutePathTo(saveFilename, true));
  }

  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  if (doTiming) {
    print("Total time elapsed: " + std::to_string(elapsed.count() / MILLI_PER_SECOND) + "s");
  }

  Nash::shutdown();
}