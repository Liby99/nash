#ifndef COEFS_PRINTER_HPP
#define COEFS_PRINTER_HPP

#include <nash/nash.h>
#include "globals.hpp"

using namespace nash;

class CoefsPrinter : public Script<Object> {
public:
  bool pressing;
  int numDegree;

  CoefsPrinter(const std::string &name, int numDegree) : Script<Object>(name), pressing(false), numDegree(numDegree) {}

  void print() {
    SHColor *color = shColors[activatedSkyBox];
    std::cout << "Red:   " << color->red.toString(numDegree) << std::endl;
    std::cout << "Green: " << color->green.toString(numDegree) << std::endl;
    std::cout << "Blue:  " << color->blue.toString(numDegree) << std::endl;
  }

  virtual void update() {
    if (!pressing) {
      if (context->getKey('p')) {
        pressing = true;
        print();
      }
    } else {
      if (!context->getKey('p')) {
        pressing = false;
      }
    }
  }
};

#endif