#include "utility/shader.h"

using namespace nash;

void Shader::init() {
  if (simple) {
    initDefault();
  } else {
    shader->initFromFiles(name, path + ".vert.glsl", path + ".frag.glsl");
  }
}

void Shader::initDefault() {
  shader->init("",
               "#version 400\n"
               "layout(location=0) in vec3 position;\n"
               "layout(location=1) in vec3 normal;\n"
               "layout(location=2) in vec2 texCoord;\n"
               "out vec3 fragPosition;\n"
               "out vec3 fragNormal;\n"
               "out vec2 fragTexCoord;\n"
               "uniform mat4 model = mat4(1);\n"
               "uniform mat4 viewPersp = mat4(1);\n"
               "void main() {\n"
               "    mat4 mvp = viewPersp * model;\n"
               "    gl_Position = mvp * vec4(position, 1);\n"
               "    fragPosition = vec3(model * vec4(position, 1));\n"
               "    fragNormal = vec3(transpose(inverse(model)) * vec4(normal, 0));\n"
               "    fragTexCoord = texCoord;\n"
               "}",
               "#version 400\n"
               "in vec3 fragPosition;\n"
               "in vec3 fragNormal;\n"
               "in vec2 fragTexCoord;\n"
               "uniform vec3 AmbientColor = vec3(0.3);\n"
               "uniform vec3 LightDirection = normalize(vec3(1, 5, 2));\n"
               "uniform vec3 LightColor = vec3(0.8);\n"
               "uniform vec3 DiffuseColor = vec3(0.3);\n"
               "out vec4 finalColor;\n"
               "void main() {\n"
               "    vec3 irradiance = AmbientColor + LightColor * max(0, "
               "dot(LightDirection, fragNormal));\n"
               "    vec3 reflectance = irradiance * DiffuseColor;\n"
               "    finalColor = vec4(sqrt(reflectance), 1);\n"
               "}");
}

void Shader::bind() { shader->bind(); }

void Shader::free() { shader->free(); }

void Shader::setUniform(const std::string &name, const Matrix4f &mat) {
  shader->setUniform(name, mat);
}

void Shader::setUniform(const std::string &name, const Matrix3f &mat) {
  shader->setUniform(name, mat);
}

void Shader::setUniform(const std::string &name, const Vector4f &vec) {
  shader->setUniform(name, vec);
}

void Shader::setUniform(const std::string &name, const Vector3f &vec) {
  shader->setUniform(name, vec);
}

void Shader::setUniform(const std::string &name, bool value) { shader->setUniform(name, value); }

void Shader::setUniform(const std::string &name, int value) { shader->setUniform(name, value); }

void Shader::setUniform(const std::string &name, float value) { shader->setUniform(name, value); }

void Shader::uploadAttr(const std::string &name, const MatrixXf &m) {
  shader->uploadAttrib(name, m);
}

void Shader::freeAttr(const std::string &name) { shader->freeAttrib(name); }

bool Shader::hasAttr(const std::string &name) { return shader->hasAttrib(name); }

void Shader::shareAttr(const Shader &other, const std::string &name, const std::string &as) {
  shader->shareAttrib(*(other.shader), name, as);
}

void Shader::uploadIndices(const nanogui::MatrixXu &m) { shader->uploadIndices(m); }

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

void Shader::freeAll() {
  for (auto it = store.begin(); it != store.end(); ++it) {
    it->second->free();
    delete it->second;
  }
}

Shader &Shader::get(const std::string &name) {
  if (store.count(name) == 1) {
    return *(store[name]);
  } else {
    Shader *shader = new Shader(name);
    store[name] = shader;
    return *shader;
  }
}

Shader &Shader::get() {
  if (store.count("") == 1) {
    return *(store[""]);
  } else {
    Shader *shader = new Shader();
    store[""] = shader;
    return *shader;
  }
}

Shader::Shader() : name(""), path(""), simple(true), shader(new nanogui::GLShader()) {
  // Do nothing
}

Shader::Shader(const std::string &name)
    : name(name), path(Path::getAbsolutePathTo(name)), simple(false),
      shader(new nanogui::GLShader()) {
  // Do nothing
}

Shader::~Shader() { delete shader; }

std::map<std::string, Shader *> Shader::store = std::map<std::string, Shader *>();
