#ifndef SPHERE_LOOPER_HPP
#define SPHERE_LOOPER_HPP

#include "sky_box_looper.hpp"

class SphereLooper : public SkyBoxLooper {
public:
  bool pressing, showing;

  SphereLooper(const std::string &name, int id, int total) : SkyBoxLooper(name, id, total), pressing(false), showing(false) {}

  virtual void update() {

    // First update the parent setting
    SkyBoxLooper::update();

    // Then update our own toggle
    if (!pressing) {
      if (context->getKey('t')) {
        pressing = true;
        showing = !showing;
      }
    } else {
      if (!context->getKey('t')) {
        pressing = false;
      }
    }

    // If both are in the enabled state, then we show the sphere. Otherwise hide.
    target->setHidden(curr != id || !showing);
  }
};

#endif