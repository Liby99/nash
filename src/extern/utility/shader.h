#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <nanogui/nanogui.h>
#include "utility/math.h"

namespace nash {
  class Shader {
  public:
    void bind();
    void free();
    void setUniform(const std::string & name, const Matrix4f & mat);
    void setUniform(const std::string & name, const Matrix3f & mat);
    void setUniform(const std::string & name, const Vector4f & vec);
    void setUniform(const std::string & name, const Vector3f & vec);
    void setUniform(const std::string & name, bool value);
    void setUniform(const std::string & name, int value);
    void setUniform(const std::string & name, float value);
    template<typename Mat>
    void uploadAttr(const std::string & name, const Mat & m);
    void freeAttr(const std::string & name);
    bool hasAttr(const std::string & name);
    void shareAttr(const Shader & other, const std::string & name, const std::string & as);
    template<typename Mat>
    void uploadIndices(const Mat & m);
    void drawArray(int type, uint32_t offset, uint32_t count);
    void drawIndexed(int type, uint32_t offset, uint32_t count);

    static void initAll();
    static Shader & get(std::string & name);
  private:
    std::string name;
    nanogui::GLShader * shader;
    Shader(std::string & name);
    ~Shader();
    void init();

    static std::map<std::string, Shader *> store;
  };
}

#endif
