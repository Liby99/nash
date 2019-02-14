#include "adhoc/sh/sh_sample.h"

using namespace nash;

SHSample::SHSample(float theta, float phi, int numDegree)
    : theta(theta), phi(phi), numDegree(numDegree) {
  coefs = new float[getNumCoefs()];
}

int SHSample::getNumCoefs() const { return numDegree * numDegree; }

float SHSample::get(int l, int m) const { return coefs[getCoefIndex(l, m)]; }

void SHSample::add(int l, int m, float coef) { coefs[getCoefIndex(l, m)] += coef; }

void SHSample::normalize(float count) {
  int count = getNumCoefs();
  for (int i = 0; i < count; i++) {
    coefs[i] /= count;
  }
}

int SHSample::getCoefIndex(int l, int m) { return l * l - l - m; }