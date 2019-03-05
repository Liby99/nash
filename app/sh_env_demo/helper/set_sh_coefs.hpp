#ifndef SET_SH_COEFS_HPP
#define SET_SH_COEFS_HPP

#include <nash/nash.h>
#include "globals.hpp"

using namespace nash;

class SetSHCoefs : public Script<Object> {
public:
  int numDegree;
  const SHCoefs *red, *green, *blue;

  SetSHCoefs(const std::string &name, int numDegree)
      : Script<Object>(name), numDegree(numDegree), red(nullptr), green(nullptr), blue(nullptr) {}

  virtual void update() {
    SHColor &color = *shColors[activatedSkyBox];
    red = &color.red;
    green = &color.green;
    blue = &color.blue;
  }

  virtual void preRender() {
    setShaderCoefs(red, "redEnvCoefs");
    setShaderCoefs(green, "greenEnvCoefs");
    setShaderCoefs(blue, "blueEnvCoefs");
  }

private:
  void setShaderCoefs(const SHCoefs *coefs, const std::string &name) {

    // Step into realm of pure opengl...
    GLuint loc = glGetUniformLocation(target->getShader().getProgramId(), name.c_str());
    glUniform1fv(loc, SH::getNumCoefs(numDegree), coefs->data());
  }
};

#endif