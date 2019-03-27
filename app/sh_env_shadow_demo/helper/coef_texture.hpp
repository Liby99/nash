#include <nash/nash.h>

namespace nash {
  class CoefTexture : public Script<Object> {
  public:
    CoefTexture(const Texture& texture, int size, const std::string &name)
      : Script<Object>(name), texture(texture), size(size) {
      // Do Nothing
    }

    virtual void preRender() {
      texture.bind(0);
      target->getShader().setUniform("tex", 0);
      target->getShader().setUniform("size", size);
    }
  private:
    const int size;
    const Texture & texture;
  };
}