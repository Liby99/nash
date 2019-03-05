#ifndef COEFS_UPDATOR_HPP
#define COEFS_UPDATOR_HPP

#include <nash/nash.h>
#include "set_sh_coefs.hpp"
#include "globals.hpp"

using namespace nash;

class CoefsUpdator : public Script<Object> {
public:
  CoefsUpdator(const std::string &name) : Script<Object>(name) {}

  virtual void update() {
    SetSHCoefs &setter = static_cast<SetSHCoefs &>(target->getScript("setter"));
    SkyBoxSHCalculator &calculator = *calculators[activatedSkyBox];
    std::vector<SHCoefs *> coefs = calculator.getCoefsList();
    setter.setRed(*coefs[0]);
    setter.setGreen(*coefs[1]);
    setter.setBlue(*coefs[2]);
  }
};

#endif