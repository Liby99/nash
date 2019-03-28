#include <nash/nash.h>

namespace nash {
  class EnvCoefBinder : public Script<Object> {
  public:
    int numDegree;

    EnvCoefBinder(const CubeMap &envMap, int numDegree, int gap, const std::string &name)
      : numDegree(numDegree), Script<Object>(name) {

      // Calculate the skybox sh
      SkyBoxSHCalculator calc(envMap, numDegree, gap);

      auto list = calc.getCoefsList();
      red = new SHCoefs(*list[0]);
      green = new SHCoefs(*list[1]);
      blue = new SHCoefs(*list[2]);

      std::cout << red->toString() << std::endl;
      std::cout << green->toString() << std::endl;
      std::cout << blue->toString() << std::endl;
    }

    virtual void preRender() {
      setShaderCoefs(red, "redEnvCoef");
      setShaderCoefs(green, "greenEnvCoef");
      setShaderCoefs(blue, "blueEnvCoef");
    }

  private:
    SHCoefs *red, *green, *blue;

    void setShaderCoefs(const SHCoefs *coefs, const std::string &name) {
      target->getShader().setUniform(name, coefs->data(), SH::getNumCoefs(numDegree));
    }
  };
}