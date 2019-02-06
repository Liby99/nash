#ifndef CONTEXT_H
#define CONTEXT_H

#include <ctype.h>
#include <vector>
#include <nanogui/nanogui.h>
#include "utility/math.h"

namespace nash {
  enum Direction { Up, Down, Left, Right };

  class Context {
  public:
    Context();

    void init();
    void endOfFrameCycle();

    bool getKey(char key);
    bool getDirectionKey(Direction dir);
    bool getMouseLeft();
    bool getMouseRight();
    bool cursorIsInside();
    const Vector2i & getCursorPosition();
    Vector2i getCursorMovement();
    const Vector2f & getScrollPosition();
    Vector2f getScrollMovement();

    bool keyboardEvent(int key, int scancode, int action, int modifiers);
    bool mouseButtonEvent(const Vector2i & p, int button, bool down, int modifiers);
    bool mouseMotionEvent(const Vector2i & p, int button, int modifiers);
    bool mouseEnterEvent(const Vector2i & p, bool enter);
    bool scrollEvent(const Vector2i & p, const Vector2f & rel);

  private:
    bool shiftStatus, ctrlStatus, altStatus, superStatus;
    std::vector<bool> keyStatus;
    bool leftButtonDown, rightButtonDown, cursorInside;
    Vector2i cursorPosition, newCursorPosition;
    Vector2f scrollPosition, newScrollPosition;

    void extractModifiers(int modifiers);
  };
}

#endif
