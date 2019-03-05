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
    SHCoefs(const SHCoefs &other);
    ~SHCoefs();

    float get(int l, int m) const;
    float get(int index) const;
    void set(int l, int m, float v);
    void set(int index, float v);
    void accumulate(int l, int m, float v);
    void accumulate(int index, float v);
    void normalize(float factor);
    float eval(float theta, float phi) const;
    float *data() const;
    int size() const;

    std::string toString() const;
    std::string toString(int d) const;
  };
}

#endif