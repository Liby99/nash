#ifndef SH_COLOR_SPHERES_HPP
#define SH_COLOR_SPHERES_HPP

#include <nash/nash.h>

using namespace nash;

class SHColorSpheres : public Object {
public:
  SHColorSpheres(const SHColor &color) : Object(), color(color) {

    // First construct three spheres
    redSphere = new SHSphere(color.red);
    redSphere->transform.position.x() -= 1; // Red sphere shift to the left
    greenSphere = new SHSphere(color.green);
    // Green sphere in the center
    blueSphere = new SHSphere(color.blue);
    blueSphere->transform.position.x() += 1; // Blue sphere shift to the right

    // Then we set this as the parent object
    redSphere->setParent(*this);
    greenSphere->setParent(*this);
    blueSphere->setParent(*this);
  }

  ~SHColorSpheres() {
    delete redSphere;
    delete greenSphere;
    delete blueSphere;
  }

private:
  SHColor color;
  SHSphere *redSphere, *greenSphere, *blueSphere;
};

#endif