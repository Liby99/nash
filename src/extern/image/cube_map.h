#ifndef CUBE_MAP_H
#define CUBE_MAP_H

#include "image/image.h"
#include "image/texture.h"

namespace nash {
  class CubeMap : public Texture {
  public:
    CubeMap(const Image &top, const Image &down, const Image &left, const Image &right,
            const Image &front, const Image &back);

    virtual void init();
    virtual void bind(GLuint pos) const;
    Vector4u getColor(Vector3f dir) const;

  protected:
    const Image *top, *down, *left, *right, *front, *back;
  };
}

#endif