#ifndef INIT_H
#define INIT_H

#include <nanogui/nanogui.h>
#include "utility/path.h"

namespace nash {
  class Nash {
  public:
    static void init();
    static void init(int argc, char * argv[]);
    static void shutdown();
  };
}

#endif
