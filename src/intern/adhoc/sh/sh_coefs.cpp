#include "adhoc/sh/sh_coefs.h"

using namespace nash;

SHCoefs::SHCoefs() : numDegree(0), coefs(nullptr) {}

SHCoefs::SHCoefs(int numDegree) : numDegree(numDegree) {
  int numCoefs = SH::getNumCoefs(numDegree);
  coefs = new float[numCoefs];
  for (int i = 0; i < numCoefs; i++) {
    coefs[i] = 0;
  }
}

SHCoefs::SHCoefs(const SHCoefs &other) : numDegree(other.numDegree) {
  int numCoefs = SH::getNumCoefs(numDegree);
  coefs = new float[numCoefs];
  for (int i = 0; i < numCoefs; i++) {
    coefs[i] = other.get(i);
  }
}

SHCoefs::~SHCoefs() {
  if (coefs != nullptr) {
    delete coefs;
  }
}

float SHCoefs::get(int l, int m) const { return get(SH::getCoefIndex(l, m)); }

float SHCoefs::get(int index) const { return coefs[index]; }

void SHCoefs::set(int l, int m, float v) { set(SH::getCoefIndex(l, m), v); }

void SHCoefs::set(int index, float v) { coefs[index] = v; }

void SHCoefs::accumulate(int l, int m, float v) { accumulate(SH::getCoefIndex(l, m), v); }

void SHCoefs::accumulate(int index, float v) { coefs[index] += v; }

void SHCoefs::normalize(float factor) {
  int numCoefs = SH::getNumCoefs(numDegree);
  for (int i = 0; i < numCoefs; i++) {
    coefs[i] *= factor;
  }
}

float SHCoefs::eval(float theta, float phi) const {
  float sum = 0;
  for (int l = 0; l < numDegree; l++) {
    for (int m = -l; m <= l; m++) {
      int index = SH::getCoefIndex(l, m);
      sum += SH::y(l, m, theta, phi) * coefs[index];
    }
  }
  return sum;
}

std::string SHCoefs::toString() const {
  std::string str = "coef{" + std::to_string(numDegree) + "}: [";
  int numCoefs = SH::getNumCoefs(numDegree);
  for (int i = 0; i < numCoefs; i++) {
    str += std::to_string(coefs[i]) + (i < numCoefs - 1 ? ", " : "]");
  }
  return str;
}