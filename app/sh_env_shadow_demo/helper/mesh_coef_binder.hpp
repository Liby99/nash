#ifndef MESH_COEF_BINDER
#define MESH_COEF_BINDER

#include <nash/nash.h>

namespace nash {
  class MeshCoefBinder : public Script<Object> {
  public:
    int numDegree;

    MeshCoefBinder(const std::string &name, int numDegree)
        : numDegree(numDegree), Script<Object>(name) {}

    virtual void onAttach(const Object &target) {
      mesh = (Mesh *)&target;

      // Calculate the general things
      int numCoefs = SH::getNumCoefs(numDegree);
      int numVertices = mesh->getPositions().cols();
      int numPixelsPerVertex = std::ceil(numCoefs / 4.0f);
      int numPixels = numPixelsPerVertex * numVertices;
      int textureSideLength = std::ceil(sqrt((float) numPixels)); // Has to be square

      std::cout << "Num Coefs: " << numCoefs << std::endl;
      std::cout << "Num Vertices: " << numVertices << std::endl;
      std::cout << "Num Pixels Per Vertex: " << numPixelsPerVertex << std::endl;
      std::cout << "Num Pixels: " << numPixels << std::endl;
      std::cout << "Texture Side Length: " << textureSideLength << std::endl;

      // Generate textureIndex, which is (int, int).
      textureIndices = MatrixXu(2, numVertices);
      for (int i = 0; i < textureIndices.cols(); i++) {
        int x = i % textureSideLength;
        int y = i * numPixelsPerVertex / textureSideLength;
        textureIndices.col(i) << x, y;
      }

      // Calculate mesh sh coefs
      MeshSHCalculator calc(*mesh, numDegree);

      // Build the image from coefs
      const std::vector<SHCoefs *> &list = calc.getCoefsList();
      textureImage = new Image(textureSideLength, textureSideLength);
      for (int i = 0; i < numVertices; i++) {
        Vector2u xy = textureIndices.col(i);
        for (int j = 0; j < numCoefs; j++) {
          int coefRow = j / 4;
          int coefSlot = j % 4;
          unsigned char val = (list[i]->get(j) / 4.0f + 0.5f) * 255;
          textureImage->setChannel(xy[1] + coefRow, xy[0], coefSlot, val);
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
    MatrixXu textureIndices;
    Mesh *mesh;
    Image *textureImage;
    TextureRect *texture;
  };
}

#endif