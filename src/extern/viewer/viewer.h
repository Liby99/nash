#ifndef VIEWER_H
#define VIEWER_H

#include "viewer/canvas.h"

namespace nash {
  class Viewer : public nanogui::Screen {
  public:
    static const nanogui::Color BACKGROUND;
    static const int HEADER_HEIGHT, PADDING;

    Viewer(int width, int height, std::string name, Scene &scene);
    void start();
    virtual bool keyboardEvent(int, int, int, int);
    virtual void draw(NVGcontext *);

  protected:
    nanogui::Window *sceneWindow;
    Canvas *sceneCanvas;
  };
}

#endif
