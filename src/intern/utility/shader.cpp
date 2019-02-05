#include "utility/shader.h"

using namespace nash;

void Shader::bind() {
  shader->bind();
}

void Shader::free() {
  shader->free();
}

void Shader::setUniform(const std::string & name, const Matrix4f & mat) {
  shader->setUniform(name, mat);
}

void Shader::setUniform(const std::string & name, const Matrix3f & mat) {
  shader->setUniform(name, mat);
}

void Shader::setUniform(const std::string & name, const Vector4f & vec) {
  shader->setUniform(name, vec);
}

void Shader::setUniform(const std::string & name, const Vector3f & vec) {
  shader->setUniform(name, vec);
}

void Shader::setUniform(const std::string & name, bool value) {
  shader->setUniform(name, value);
}

void Shader::setUniform(const std::string & name, int value) {
  shader->setUniform(name, value);
}

void Shader::setUniform(const std::string & name, float value) {
  shader->setUniform(name, value);
}

template<typename Mat>
void Shader::uploadAttr(const std::string & name, const Mat & m) {
  shader->uploadAttrib(name, m);
}

void Shader::freeAttr(const std::string & name) {
  shader->freeAttrib(name);
}

bool Shader::hasAttr(const std::string & name) {
  return shader->hasAttrib(name);
}

void Shader::shareAttr(const Shader & other, const std::string & name, const std::string & as) {
  shader->shareAttrib(*(other.shader), name, as);
}

template<typename Mat>
void Shader::uploadIndices(const Mat & m) {
  shader->uploadIndices(m);
}

void Shader::drawArray(int type, uint32_t offset, uint32_t count) {
  shader->drawArray(type, offset, count);
}

void Shader::drawIndexed(int type, uint32_t offset, uint32_t count) {
  shader->drawIndexed(type, offset, count);
}

void Shader::initAll() {
  for (auto it = store.begin(); it != store.end(); ++it) {
    it->second->init();
  }
}

Shader & Shader::get(std::string & name) {
  if (store.count(name) == 1) {
    return *(store[name]);
  } else {
    Shader * shader = new Shader(name);
    store[name] = shader;
    return *shader;
  }
}

Shader::Shader(std::string & name) : name(name), shader(new nanogui::GLShader()) {
  // Do nothing
}

Shader::~Shader() {
  delete shader;
}

void Shader::init() {
  shader->initFromFiles(name, name + ".vert.glsl", name + ".frag.glsl");
}

std::map<std::string, Shader *> Shader::store = std::map<std::string, Shader *>();
