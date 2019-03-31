#include <nash/nash.h>

namespace nash {
  class MeshCoefBinder : public Script<Object> {
  public:
    static const int CHANNEL_PER_PIXEL = 4;

    MeshCoefBinder(const std::string &filename, int numDegree, const std::string &name)
      : filename(filename), numDegree(numDegree), Script<Object>(name) {
      // Do nothing
    }

    virtual void start() {
      const Mesh *meshp = (Mesh *) target;

      // Then start loading the mesh coefs
      SHFile file(numDegree);
      file.load(filename);
      const std::vector<SHCoefs *> &list = file.getCoefsList();

      // Setup basic variables
      int numVertices = list.size();
      int numCoefs = SH::getNumCoefs(numDegree);
      int numPixelsPerVertex = std::ceil(numCoefs / CHANNEL_PER_PIXEL);
      int numData = numVertices * numPixelsPerVertex * CHANNEL_PER_PIXEL;

      // Setup the float array
      indices = MatrixXf(1, numVertices);
      GLfloat *bufferArray = new float[numData];
      for (int i = 0; i < numVertices; i++) {
        int start = i * numPixelsPerVertex * CHANNEL_PER_PIXEL;
        indices.col(i) << i * numPixelsPerVertex;
        for (int j = 0; j < numCoefs; j++) {
          bufferArray[start + j] = list[i]->get(j);
        }
      }

      // Setup the buffer from the array
      int totalSize = numData * sizeof(GLfloat);
      GLuint texBuffer;
      glGenBuffers(1, &texBuffer);
      glBindBuffer(GL_TEXTURE_BUFFER, texBuffer);
      glBufferData(GL_TEXTURE_BUFFER, totalSize, bufferArray, GL_STATIC_DRAW);
      glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, texBuffer);

      // Delete the float array since we no longer need it.
      delete [] bufferArray;

      // Assign the value of texBuffer
      bufferTextureId = texBuffer;
    }

    virtual void preRender() {

      // Bind the texture
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_BUFFER, bufferTextureId);
      target->getShader().setUniform("objShadowCoefSampler", 0);

      // Bind the indices
      target->getShader().uploadAttr("objShadowCoefIndex", indices);
    }

  private:
    const std::string &filename;
    int numDegree;
    GLuint bufferTextureId;
    MatrixXf indices;
  };
}