#ifndef SKY_BOX_SH_CALCULATOR_H
#define SKY_BOX_SH_CALCULATOR_H

#include "adhoc/sh/sh_coefs.h"
#include "image/cube_map.h"

namespace nash {
  class SkyBoxSHCalculator {
  public:
    static const int NUM_CHANNEL;
    static const int SAMPLE_COUNT;
    int numDegree;
    SkyBoxSHCalculator(const CubeMap &cubeMap, int numDegree);
    // ~SkyBoxSHCalculator();
    const std::vector<SHCoefs *> &getCoefsList();

  private:
    const CubeMap &cubeMap;
    std::vector<SHCoefs *> coefsList;
  };
}

#endif