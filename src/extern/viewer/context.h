#ifndef CONTEXT_H
#define CONTEXT_H

#include "utility/math.h"
#include <ctype.h>
#include <nanogui/nanogui.h>
#include <vector>

namespace nash {
  enum Direction { Up, Down, Left, Right };

  class Context {
  public:
    Context();

    // Life cycle event
    void init();
    void bindGLFWWindow(GLFWwindow *window);
    void endOfFrameCycle();

    // Window properties
    GLFWwindow *getGLFWWindow();
    int getWindowWidth();
    int getWindowHeight();
    void resetCursor();
    void hideCursor();
    void disableCursor();
    void setCursorPos(int x, int y);
    void centerCursorPos();

    // User Input from keyboard and mouse
    bool getKey(char key);
    bool getDirectionKey(Direction dir);
    bool getMouseLeft();
    bool getMouseRight();
    bool cursorIsInside();
    const Vector2i &getCursorPosition();
    Vector2i getCursorMovement();
    const Vector2f &getScrollPosition();
    Vector2f getScrollMovement();

    // Event Callbacks
    bool keyboardEvent(int key, int scancode, int action, int modifiers);
    bool mouseButtonEvent(const Vector2i &p, int button, bool down, int modifiers);
    bool mouseMotionEvent(const Vector2i &p, const Vector2i &rel, int button, int modifiers);
    bool mouseEnterEvent(const Vector2i &p, bool enter);
    bool scrollEvent(const Vector2i &p, const Vector2f &rel);

  private:
    GLFWwindow *window;
    int windowWidth, windowHeight;

    std::vector<bool> keyStatus;
    bool shiftStatus, ctrlStatus, altStatus, superStatus;
    bool leftButtonDown, rightButtonDown, cursorInside;
    Vector2i exactCursorPosition, cursorPosition, newCursorPosition;
    Vector2f scrollPosition, newScrollPosition;

    void extractModifiers(int modifiers);
  };
} 

#endif
