#ifndef MESH_COEF_BINDER
#define MESH_COEF_BINDER

#include <nash/nash.h>

namespace nash {
  class MeshCoefBinder : public Script<Object> {
  public:
    int numDegree;

    MeshCoefBinder(int numDegree, const std::string &name)
        : numDegree(numDegree), Script<Object>(name) {}

    /**
     * See nash/lab/texture-filling for example and graphics demonstration
     */
    int findTextureSideLength(int numVertices, int numPixelsPerVertex) {
      int baseline = std::ceil(std::sqrt(numVertices * numPixelsPerVertex));
      while (std::ceil((float) numVertices / baseline) * numPixelsPerVertex > baseline)
        baseline += 1;
      return baseline;
    }

    virtual void onAttach(const Object &target) {
      mesh = (Mesh *)&target;

      // Calculate the general things
      int numCoefs = SH::getNumCoefs(numDegree);
      int numVertices = mesh->getPositions().cols();
      int numPixelsPerVertex = std::ceil(numCoefs / 4.0f);
      int textureSideLength = findTextureSideLength(numVertices, numPixelsPerVertex);
      int totalNumPixels = textureSideLength * textureSideLength;

      // Pre-filling
      textureIndices = MatrixXf(2, numVertices); // Setup index
      MeshSHCalculator calc(*mesh, numDegree); // Calculate mesh sh coefs

      // Build the image from coefs
      const std::vector<SHCoefs *> &list = calc.getCoefsList();
      textureImage = new Image(textureSideLength, textureSideLength);
      for (int i = 0; i < numVertices; i++) {

        // Generate textureIndex, which is (int, int).
        int x = i % textureSideLength;
        int y = (i / textureSideLength) * numPixelsPerVertex;
        textureIndices.col(i) << x, y;

        // Fill in the image
        for (int j = 0; j < numCoefs; j++) {
          int coefRow = j / 4;
          int coefSlot = j % 4;
          unsigned char val = (list[i]->get(j) / 4.0f + 0.5f) * 255;
          textureImage->setChannel(x, y + coefRow, coefSlot, val);
        }
      }

      // Setup the texture from image
      texture = new TextureRect(*textureImage);
    }

    virtual void preRender() {
      target->getShader().uploadAttr("objShadowCoefIndex", textureIndices);
      target->getShader().setUniform("objShadowCoefSampler", 0);
      texture->bind(0);
    }

    const Image &getImage() {
      return *textureImage;
    }

    int getTextureWidth() const {
      return textureImage->width;
    }

    int getTextureHeight() const {
      return textureImage->height;
    }

    const TextureRect & getTexture() {
      return *texture;
    }

  private:
    MatrixXf textureIndices;
    Mesh *mesh;
    Image *textureImage;
    TextureRect *texture;
  };
}

#endif