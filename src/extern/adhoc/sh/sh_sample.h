#ifndef SH_SAMPLE_H
#define SH_SAMPLE_H

namespace nash {
  class SHSample {
  public:
    float theta, phi;
    int numDegree;
    float * coefs;

    SHSample(float theta, float phi, int numDegree);
    int getNumCoefs() const;
    float get(int l, int m) const;
    void add(int l, int m, float coef);
    void normalize(float count);
    
    static int getCoefIndex(int l, int m);
  };
}

#endif