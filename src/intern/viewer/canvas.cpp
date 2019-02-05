#include "viewer/canvas.h"

using namespace nash;

Canvas::Canvas(nanogui::Widget * parent, Scene & s) : nanogui::GLCanvas(parent), scene(&s) {
  // Do nothing
}

Canvas::~Canvas() {

}

void Canvas::setSize(int width, int height) {
  GLCanvas::setSize({ width, height });
  scene->setSize(width, height);
}

void Canvas::start() {
  scene->start();
}

void Canvas::drawGL() {
  glEnable(GL_DEPTH_TEST);
  scene->update();
  scene->render();
  glDisable(GL_DEPTH_TEST);
}
