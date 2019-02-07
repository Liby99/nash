#ifndef INIT_H
#define INIT_H

#include "utility/path.h"
#include <nanogui/nanogui.h>

namespace nash {
class Nash {
public:
  static void init();
  static void init(int argc, char *argv[]);
  static void shutdown();
};
} // namespace nash

#endif
