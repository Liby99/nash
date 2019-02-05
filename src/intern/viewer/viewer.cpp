#include "viewer/viewer.h"

#include <iostream>

using namespace nash;

const nanogui::Color Viewer::BACKGROUND = { 30, 30, 30, 255 };

const int Viewer::HEADER_HEIGHT = 28;

const int Viewer::PADDING = 5;

Viewer::Viewer(int w, int h, std::string name, Scene & scene) :
  nanogui::Screen(Vector2i(w, h), name, false) {

  std::cout << "test test 1" << std::endl;
  using namespace nanogui;
  setBackground(BACKGROUND);
  sceneWindow = new Window(this, "Scene Viewer");
  sceneWindow->setLayout(new GroupLayout(PADDING));
  sceneCanvas = new Canvas(sceneWindow, scene);
  sceneCanvas->setBackgroundColor(BACKGROUND);
  sceneCanvas->setSize(w - 2 * PADDING, h - HEADER_HEIGHT - 2 * PADDING);

  std::cout << "test test 1" << std::endl;
}

void Viewer::start() {
  std::cout << "test 1" << std::endl;
  nanogui::init();
  std::cout << "test 2" << std::endl;
  Shader::initAll();
  std::cout << "test 3" << std::endl;
  sceneCanvas->start();
  std::cout << "test 4" << std::endl;
  performLayout();
  drawAll();
  setVisible(true);
  std::cout << "test 5" << std::endl;
  nanogui::mainloop();
  Shader::freeAll();
  nanogui::shutdown();
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
