#include "adhoc/sh/sky_box_sh_calculator.h"
#include "utility/sampler.h"

using namespace nash;

const int SkyBoxSHCalculator::NUM_CHANNEL = 3;

const int SkyBoxSHCalculator::SAMPLE_COUNT = 25000;

SkyBoxSHCalculator::SkyBoxSHCalculator(const CubeMap &cubeMap, int numDegree, int numGap)
    : cubeMap(cubeMap), numDegree(numDegree) {

  coefsList = std::vector<SHCoefs *>(NUM_CHANNEL);
  coefsList[0] = new SHCoefs(numDegree);
  coefsList[1] = new SHCoefs(numDegree);
  coefsList[2] = new SHCoefs(numDegree);

  // std::vector<Vector3f> samples(SAMPLE_COUNT);
  // Sampler::sampleSphere(samples);
  // float factor = 4.0f * PI / SAMPLE_COUNT;

  // for (int i = 0; i < samples.size(); i++) {
  //   Vector4u color = cubeMap.getColor(samples[i]);
  //   Vector2f thetaPhi = Math::normalCartToPolar(samples[i]);
  //   float theta = thetaPhi.x(), phi = thetaPhi.y();
  //   for (int l = 0; l < numDegree; l++) {
  //     for (int m = -l; m <= l; m++) {
  //       float y = SH::y(l, m, theta, phi);
  //       coefsList[0]->accumulate(l, m, color[0] / 255.0f * y);
  //       coefsList[1]->accumulate(l, m, color[1] / 255.0f * y);
  //       coefsList[2]->accumulate(l, m, color[2] / 255.0f * y);
  //     }
  //   }
  // }

  // coefsList[0]->normalize(factor);
  // coefsList[1]->normalize(factor);
  // coefsList[2]->normalize(factor);

  for (CubeMap::Face face : CubeMap::FACES) {
    const Image &img = cubeMap.getImage(face);
    float area = PI * 4 * (numGap * numGap) / (img.width * img.height * 6.0f);
    Vector3f centralDir = cubeMap.getCentralDirection(face);

#pragma omp parallel for collapse(2)
    for (int j = numGap / 2; j < img.height; j += numGap) {
      // Loop height first to improve cache performance
      for (int i = numGap / 2; i < img.width; i += numGap) {

        // Get the raw color
        Vector4u rawColor = img.getColor(i, j);
        Vector3f color(rawColor[0] / 255.0f, rawColor[1] / 255.0f, rawColor[2] / 255.0f);

        // Get the direction to the pixel
        Vector3f dir = cubeMap.getDirectionTo(face, i, j);
        Vector2f thetaPhi = Math::normalCartToPolar(dir);
        float theta = thetaPhi.x(), phi = thetaPhi.y();

        // The weight of this pixel is based on the area and the cosine value of the angle
        // between the pixel direction and the central direction of the image
        Vector3f d1 = dir, d2 = dir;
        if (centralDir.x() != 0)
          d1.y() = d2.z() = 0;
        else if (centralDir.y() != 0)
          d1.x() = d2.z() = 0;
        else
          d1.x() = d2.y() = 0;
        float weight = area * d1.dot(centralDir) * d2.dot(centralDir);
        for (int l = 0; l < numDegree; l++) {
          for (int m = -l; m <= l; m++) {
            float y = SH::y(l, m, theta, phi);
            coefsList[0]->accumulate(l, m, weight * y * color[0]);
            coefsList[1]->accumulate(l, m, weight * y * color[1]);
            coefsList[2]->accumulate(l, m, weight * y * color[2]);
          }
        }
      }
    }
  }
}

SkyBoxSHCalculator::~SkyBoxSHCalculator() {
  for (int i = 0; i < NUM_CHANNEL; i++) {
    delete coefsList[i];
  }
}

const std::vector<SHCoefs *> &SkyBoxSHCalculator::getCoefsList() { return coefsList; }