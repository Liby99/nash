#ifndef SH_COEFS_H
#define SH_COEFS_H

#include "adhoc/sh/sh.h"

namespace nash {
  class SHCoefs {
  public:
    int numDegree;
    float *coefs;

    SHCoefs();
    SHCoefs(int numDegree);
    ~SHCoefs();

    float get(int l, int m) const;
    float get(int index) const;
    void set(int l, int m, float v);
    void set(int index, float v);
    void accumulate(int l, int m, float v);
    void accumulate(int index, float v);
    void normalize(float factor);
    float eval(float theta, float phi) const;
  };
}

#endif