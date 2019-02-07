#include "utility/path.h"

using namespace nash;

std::string Path::argv0 = std::string("");

void Path::init(char * a0) {
  argv0 = std::string(a0);
}

const std::string & Path::getArgv0() {
  return argv0;
}

std::string Path::getCurrentWorkingDirectory() {
#if defined(__APPLE__)
  char buffer[BUF_SIZE];
  return std::string(getcwd(buffer, BUF_SIZE));
#endif
}

std::string Path::getProgramDirectory() {
#if defined(__APPLE__)
  if (getArgv0().size() > 0 && getArgv0()[0] == '/') {
    return getDirectory(getArgv0());
  } else {
    return getCurrentWorkingDirectory() + "/" + getDirectory(getArgv0());
  }
#endif
}

std::string Path::getProgramFileName() {
#if defined(__APPLE__)
  return getFileName(getArgv0());
#endif
}

std::string Path::getAbsolutePathTo(const std::string & relativePath) {
#if defined(__APPLE__)
  if (relativePath[0] == '/') {
    return relativePath;
  } else {
    return getProgramDirectory() + "/" + relativePath;
  }
#endif
}

std::string Path::getFileName(const std::string & path) {
  std::size_t found = path.find_last_of("/\\");
  return path.substr(found + 1);
}

std::string Path::getDirectory(const std::string & path) {
  std::size_t found = path.find_last_of("/\\");
  return path.substr(0, found + 1);
}
