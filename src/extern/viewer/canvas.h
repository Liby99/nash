#ifndef CANVAS_H
#define CANVAS_H

#include "viewer/scene.h"

namespace nash {
  class Canvas : public nanogui::GLCanvas {
  public:
    Canvas(nanogui::Widget * parent, Scene & scene);
    ~Canvas();
    void setSize(int width, int height);
    void start();
    bool keyboardEvent(int key, int scancode, int action, int modifiers);
    virtual void drawGL();
  private:
    Scene * scene;
    Context context;
  };
}

#endif
