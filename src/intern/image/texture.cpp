#include "image/texture.h"

using namespace nash;

const GLuint &Texture::getTextureId() const { return textureId; }

Texture::Texture() : textureId(0) {}

void Texture::bind(GLuint pos) const { glActiveTexture(GL_TEXTURE0 + pos); }
