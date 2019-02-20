#include "adhoc/sh/sh.h"

using namespace nash;

/**
 * Spherical Harmonics: y
 * y_l^m(\theta, \phi) =
 * - m > 0: \sqrt{2} K_l^m \cos(m\phi) P_l^m(\cos\theta)
 * - m = 0: K_l^0 P_l^0(\cos\theta)
 * - m < 0: \sqrt{2} K_l^m \sin(-m\phi) P_l^{-m}(\cos\theta)
 */
float SH::y(int l, int m, float theta, float phi) {
  const double sqrt2 = sqrt(2.0);
  if (m > 0) {
    return sqrt2 * SH::k(l, m) * cos(m * phi) * SH::p(l, m, cos(theta));
  } else if (m == 0) {
    return SH::k(l, 0) * SH::p(l, m, cos(theta));
  } else {
    return sqrt2 * SH::k(l, -m) * sin(-m * phi) * SH::p(l, -m, cos(theta));
  }
}

/**
 * Legendre Polynomials: P
 * 1. (l - m) P_l^m = x(2l - 1) P_{l-1}^m - (l + m - 1) P_{l-2}^m
 * 2. P_m^m = (-1)^m (2m - 1)!! (1 - x ^ 2)^{m/2}
 * 3. P_{m+1}^m = x(2m + 1) P_m^m
 */
float SH::p(int l, int m, float x) {
  float pmm = 1.0;
  if (m > 0) {
    float somx2 = sqrt((1.0 - x) * (1.0 + x));
    float fact = 1.0;
    for (int i = 1; i <= m; i++) {
      pmm *= (-fact) * somx2;
      fact += 2.0;
    }
  }
  if (l == m)
    return pmm;
  float pmmp1 = x * (2.0 * m + 1.0) * pmm;
  if (l == m + 1)
    return pmmp1;
  float pll = 0.0;
  for (int ll = m + 2; ll <= l; ++ll) {
    pll = ((2.0 * ll - 1.0) * x * pmmp1 - (ll + m - 1.0) * pmm) / (ll - m);
    pmm = pmmp1;
    pmmp1 = pll;
  }
  return pll;
}

/**
 * Scaling Factor: K
 * K_l^m = \sqrt{\frac{2l + 1}{4\pi} \frac{(l-\abs{m})!}{(l+\abs{m})!}}
 */
float SH::k(int l, int m) {
  double temp = ((2.0 * l + 1.0) * factorial(l - m)) / (4.0 * PI * factorial(l + m));
  return sqrt(temp);
}

int SH::getCoefIndex(int l, int m) { return l * (l + 1) + m; }

int SH::getNumCoefs(int numDegree) { return numDegree * numDegree; }

/**
 * Calculate the factorial of i. (e.g. i!)
 */
int SH::factorial(unsigned int i) {
  const double factorial_cache[16] = {1, 1, 2, 6, 24, 120, 720, 5040,
                                      40320, 362880, 3628800, 39916800,
                                      479001600, 6227020800,
                                      87178291200, 1307674368000};

  if (i < 16) {
    return factorial_cache[i];
  } else {
    double s = 1.0;
    for (int n = 2; n <= i; n++) {
      s *= n;
    }
    return s;
  }
}
