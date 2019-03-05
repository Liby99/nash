#ifndef SKY_BOX_LOOPER_HPP
#define SKY_BOX_LOOPER_HPP

#include "looper.hpp"
#include "globals.hpp"

class SkyBoxLooper : public Looper {
public:
  SkyBoxLooper(const std::string &name, int id, int total) : Looper(name, id, total) {}

  virtual void update() {
    updateFromKey(Direction::Left, 1);
    updateFromKey(Direction::Right, -1);
    activatedSkyBox = curr;
  }
};

#endif