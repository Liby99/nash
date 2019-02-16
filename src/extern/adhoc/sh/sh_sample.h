#ifndef SH_SAMPLE_H
#define SH_SAMPLE_H

namespace nash {
  template<typename T>
  class SHSample {
    float theta, phi;
    T value;
    SHSample(float theta, float phi);
    void update(T value);
  };
}

#endif