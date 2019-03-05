#ifndef SH_COLOR_SPHERES_HPP
#define SH_COLOR_SPHERES_HPP

#include <nash/nash.h>

using namespace nash;

class SHColorSpheres : public Object {
public:
  SHColorSpheres(const SHCoefs &red, const SHCoefs &green, const SHCoefs &blue) : Object() {

    // First construct three spheres
    redSphere = new SHSphere(red);
    redSphere->transform.position.x() -= 1; // Red sphere shift to the left
    greenSphere = new SHSphere(green);
    // Green sphere in the center
    blueSphere = new SHSphere(blue);
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
  SHSphere *redSphere, *greenSphere, *blueSphere;
};

#endif