#include "viewer/context.h"

using namespace nash;

Context::Context() : keyStatus(512) {

}

void Context::init() {
  for (int i = 0; i < keyStatus.size(); i++) {
    keyStatus[i] = false;
  }
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
  shiftStatus = GLFW_MOD_SHIFT & modifiers;
  ctrlStatus = GLFW_MOD_CONTROL & modifiers;
  altStatus = GLFW_MOD_ALT & modifiers;
  superStatus = GLFW_MOD_SUPER & modifiers;

  // Always responding to keyboard event
  return true;
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
