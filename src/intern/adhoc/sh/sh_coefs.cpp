#include "adhoc/sh/sh_coefs.h"

using namespace nash;

SHCoefs::SHCoefs() {}

SHCoefs::SHCoefs(int numDegree) : numDegree(numDegree) {
  coefs = new float[SH::getNumCoefs(numDegree)];
}