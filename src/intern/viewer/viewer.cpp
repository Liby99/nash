#include "viewer/viewer.h"

using namespace nash;

const nanogui::Color Viewer::BACKGROUND = { 30, 30, 30, 255 };

const int Viewer::HEADER_HEIGHT = 28;

const int Viewer::PADDING = 5;

Viewer::Viewer(int w, int h, std::string name, Scene & scene) :
  nanogui::Screen(Vector2i(w, h), name, false) {
  using namespace nanogui;
  setBackground(BACKGROUND);
  sceneWindow = new Window(this, "Scene Viewer");
  sceneWindow->setLayout(new GroupLayout(PADDING));
  sceneCanvas = new Canvas(sceneWindow, scene);
  sceneCanvas->setBackgroundColor(BACKGROUND);
  sceneCanvas->setSize(w - 2 * PADDING, h - HEADER_HEIGHT - 2 * PADDING);
}

void Viewer::start() {
  Shader::initAll();
  sceneCanvas->start();
  performLayout();
  drawAll();
  setVisible(true);
  nanogui::mainloop();
  Shader::freeAll();
}

bool Viewer::keyboardEvent(int key, int scancode, int action, int modifiers) {
  if (Screen::keyboardEvent(key, scancode, action, modifiers)) {
    return true;
  }
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    setVisible(false);
    return true;
  }
  return false;
}

void Viewer::draw(NVGcontext * ctx) {
  Screen::draw(ctx);
}
