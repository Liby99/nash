#include "viewer/context.h"

using namespace nash;

Context::Context() : keyStatus(512) { }

void Context::init() {

  // Keys
  for (int i = 0; i < keyStatus.size(); i++) {
    keyStatus[i] = false;
  }

  // Modifier keys
  shiftStatus = false;
  ctrlStatus = false;
  altStatus = false;
  superStatus = false;

  // Mouse
  leftButtonDown = false;
  rightButtonDown = false;
  cursorInside = false;
  cursorPosition = Vector2i(0, 0);
  newCursorPosition = Vector2i(0, 0);

  // Scroll
  scrollPosition = Vector2f(0, 0);
  newScrollPosition = Vector2f(0, 0);
}

void Context::endOfFrameCycle() {
  cursorPosition = newCursorPosition;
  scrollPosition = newScrollPosition;
}

bool Context::getKey(char key) {
  switch (key) {
    case '\t': return keyStatus[GLFW_KEY_TAB];
    case '\n': return keyStatus[GLFW_KEY_ENTER];
    default: return keyStatus[toupper(key)];
  }
}

bool Context::getDirectionKey(Direction dir) {
  switch (dir) {
    case Direction::Up: return keyStatus[GLFW_KEY_UP];
    case Direction::Down: return keyStatus[GLFW_KEY_DOWN];
    case Direction::Left: return keyStatus[GLFW_KEY_LEFT];
    case Direction::Right: return keyStatus[GLFW_KEY_RIGHT];
  }
}

bool Context::getMouseLeft() {
  return leftButtonDown;
}

bool Context::getMouseRight() {
  return rightButtonDown;
}

bool Context::cursorIsInside() {
  return cursorInside;
}

const Vector2i & Context::getCursorPosition() {
  return cursorPosition;
}

Vector2i Context::getCursorMovement() {
  return newCursorPosition - cursorPosition;
}

const Vector2f & Context::getScrollPosition() {
  return scrollPosition;
}

Vector2f Context::getScrollMovement() {
  return newScrollPosition - scrollPosition;
}

bool Context::keyboardEvent(int key, int scancode, int action, int modifiers) {

  // Key status
  if (key >= 0 && key < keyStatus.size()) {
    if (action == GLFW_PRESS) {
      keyStatus[key] = true;
    } else if (action == GLFW_RELEASE) {
      keyStatus[key] = false;
    }
  }

  // Modifier status
  extractModifiers(modifiers);

  // Always responding to keyboard event
  return true;
}

bool Context::mouseButtonEvent(const Vector2i & p, int button, bool down, int modifiers) {
  if (button == GLFW_MOUSE_BUTTON_RIGHT) {
    rightButtonDown = down;
  } else if (button == GLFW_MOUSE_BUTTON_LEFT) {
    leftButtonDown = down;
  }
  extractModifiers(modifiers);
  return true;
}

bool Context::mouseMotionEvent(const Vector2i & p, int button, int modifiers) {
  newCursorPosition = p;
  cursorInside = true;
  extractModifiers(modifiers);
  return true;
}

bool Context::mouseEnterEvent(const Vector2i & p, bool enter) {
  newCursorPosition = p;
  cursorInside = enter;
  return true;
}

bool Context::scrollEvent(const Vector2i & p, const Vector2f & rel) {
  newScrollPosition = scrollPosition + rel;
  return true;
}

void Context::extractModifiers(int modifiers) {
  shiftStatus = GLFW_MOD_SHIFT & modifiers;
  ctrlStatus = GLFW_MOD_CONTROL & modifiers;
  altStatus = GLFW_MOD_ALT & modifiers;
  superStatus = GLFW_MOD_SUPER & modifiers;
}
