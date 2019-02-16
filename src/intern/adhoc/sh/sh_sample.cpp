#include "adhoc/sh/sh_sample.h"

using namespace nash;

template<typename T>
SHSample<T>::SHSample(float theta, float phi) : theta(theta), phi(phi) {}

template<typename T>
void SHSample<T>::update(T v) {
  value = v;
}
