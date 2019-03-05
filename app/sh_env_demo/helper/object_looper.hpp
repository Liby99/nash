#ifndef OBJECT_LOOPER_HPP
#define OBJECT_LOOPER_HPP

#include "looper.hpp"

class ObjectLooper : public Looper {
public:
  ObjectLooper(const std::string &name, int id, int total) : Looper(name, id, total) {}

  virtual void update() {
    updateFromKey(Direction::Up, -1);
    updateFromKey(Direction::Down, 1);
  }
};

#endif