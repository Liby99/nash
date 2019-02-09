#ifndef TEXTURE_H
#define TEXTURE_H

#include <nanogui/nanogui.h>

namespace nash {
  class Texture {
  public:
    const GLuint &getTextureId() const;
    virtual void bind(GLuint pos) const;

  protected:
    GLuint textureId;
    Texture();
  };
}

#endif
