#include "adhoc/sh/sky_box_sh_calculator.h"
#include "utility/sampler.h"

using namespace nash;

const int SkyBoxSHCalculator::NUM_CHANNEL = 3;

const int SkyBoxSHCalculator::SAMPLE_COUNT = 10000;

SkyBoxSHCalculator::SkyBoxSHCalculator(const CubeMap &cubeMap, int numDegree)
    : cubeMap(cubeMap), numDegree(numDegree) {

  coefsList = std::vector<SHCoefs *>(NUM_CHANNEL);
  coefsList[0] = new SHCoefs(numDegree);
  coefsList[1] = new SHCoefs(numDegree);
  coefsList[2] = new SHCoefs(numDegree);

  std::vector<Vector3f> samples(SAMPLE_COUNT);
  Sampler::sampleSphere(samples);
  float factor = 4.0f * PI / SAMPLE_COUNT;

  for (int i = 0; i < samples.size(); i++) {
    Vector4u color = cubeMap.getColor(samples[i]);
    Vector2f thetaPhi = Math::normalCartToPolar(samples[i]);
    float theta = thetaPhi.x(), phi = thetaPhi.y();
    for (int l = 0; l < numDegree; l++) {
      for (int m = -l; m <= l; m++) {
        float y = SH::y(l, m, theta, phi);
        coefsList[0]->accumulate(l, m, color[0] / 255.0f * y);
        coefsList[1]->accumulate(l, m, color[1] / 255.0f * y);
        coefsList[2]->accumulate(l, m, color[2] / 255.0f * y);
      }
    }
  }
  coefsList[0]->normalize(factor);
  coefsList[1]->normalize(factor);
  coefsList[2]->normalize(factor);
}

SkyBoxSHCalculator::~SkyBoxSHCalculator() {
  for (int i = 0; i < NUM_CHANNEL; i++) {
    delete coefsList[i];
  }
}

const std::vector<SHCoefs *> &SkyBoxSHCalculator::getCoefsList() { return coefsList; }