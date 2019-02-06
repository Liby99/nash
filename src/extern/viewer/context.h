#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include <nanogui/nanogui.h>

namespace nash {
  enum Direction { Up, Down, Left, Right };

  class Context {
  public:
    Context();
    void init();
    bool keyboardEvent(int key, int scancode, int action, int modifiers);
    bool getKey(char key);
    bool getDirectionKey(Direction dir);
  private:
    bool shiftStatus, ctrlStatus, altStatus, superStatus;
    std::vector<bool> keyStatus;
  };
}

#endif
