#include "adhoc/sh/sky_box_sh_calculator.h"
#include "utility/sampler.h"

using namespace nash;

const int SkyBoxSHCalculator::NUM_CHANNEL = 3;

const int SkyBoxSHCalculator::SAMPLE_COUNT = 25000;

SkyBoxSHCalculator::SkyBoxSHCalculator(const CubeMap &cubeMap, int numDegree, int numGap)
    : cubeMap(cubeMap), numDegree(numDegree) {

  // Initialize the list
  coefsList = std::vector<SHCoefs *>(NUM_CHANNEL);
  for (int i = 0; i < NUM_CHANNEL; i++) {
    coefsList[i] = new SHCoefs(numDegree);
  }

  // Store the total number of samples
  int numSamples = 0;

  // Loop through all the faces
  for (CubeMap::Face face : CubeMap::FACES) {
    const Image &img = cubeMap.getImage(face);

#pragma omp parallel for collapse(2)
    for (int j = numGap / 2; j < img.height; j += numGap) {

      // Loop height first to improve cache performance
      for (int i = numGap / 2; i < img.width; i += numGap) {
        numSamples++;

        // Get the raw color
        Vector4u rawColor = img.getColor(i, j);
        Vector3f color(rawColor[0] / 255.0f, rawColor[1] / 255.0f, rawColor[2] / 255.0f);

        // Get the direction to the pixel
        Vector3f dir = cubeMap.getDirectionTo(face, i, j);
        Vector2f thetaPhi = Math::normalCartToPolar(dir);
        float theta = thetaPhi[0], phi = thetaPhi[1];
        float x = (i * 2.0f - img.width) / img.width, y = (j * 2.0f - img.height) / img.height;
        float len = sqrt(x * x + y * y + 1);

        // Texel Solid Angle
        float weight = 1.0f / (len * len * len);
        for (int l = 0; l < numDegree; l++) {
          for (int m = -l; m <= l; m++) {
            float y = SH::y(l, m, theta, phi);
            for (int i = 0; i < NUM_CHANNEL; i++) {
              coefsList[i]->accumulate(l, m, weight * y * color[i]);
            }
          }
        }
      }
    }
  }

  float factor = 32.0f / numSamples / PI;
  for (int i = 0; i < NUM_CHANNEL; i++) {
    coefsList[i]->normalize(factor);
  }
}

SkyBoxSHCalculator::~SkyBoxSHCalculator() {
  for (int i = 0; i < NUM_CHANNEL; i++) {
    delete coefsList[i];
  }
}

const std::vector<SHCoefs *> &SkyBoxSHCalculator::getCoefsList() { return coefsList; }