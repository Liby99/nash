#include <nash/nash.h>

namespace nash {
  class EnvCoefBinder : public Script<Object> {
  public:
    int numDegree;

    EnvCoefBinder(const CubeMap &envMap, int numDegree, const std::string &name)
      : numDegree(numDegree), Script<Object>(name) {

      // Calculate the skybox sh
      SkyBoxSHCalculator calc(envMap, numDegree);

      auto list = calc.getCoefsList();
      red = SHCoefs(*list[0]);
      green = SHCoefs(*list[1]);
      blue = SHCoefs(*list[2]);
    }

    virtual void preRender() {
      setShaderCoefs(red, "redEnvCoef");
      setShaderCoefs(green, "greenEnvCoef");
      setShaderCoefs(blue, "blueEnvCoef");
    }

  private:
    SHCoefs red, green, blue;

    void setShaderCoefs(const SHCoefs &coefs, const std::string &name) {
      target->getShader().setUniform(name, coefs.data(), SH::getNumCoefs(numDegree));
    }
  };
}