#include "utility/init.h"

using namespace nash;

void Nash::init() { nanogui::init(); }

void Nash::init(int argc, char *argv[]) {
  init();
  Path::init(argv[0]);
}

void Nash::shutdown() { nanogui::shutdown(); }
