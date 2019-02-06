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
  context.init();
  scene->start(context);
}

bool Canvas::keyboardEvent(int key, int scancode, int action, int modifiers) {
  return false;
}

void Canvas::drawGL() {
  glEnable(GL_DEPTH_TEST);
  scene->update(context);
  scene->render(context);
  glDisable(GL_DEPTH_TEST);
}
