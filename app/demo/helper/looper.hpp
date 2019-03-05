#ifndef LOOPER_HPP
#define LOOPER_HPP

#include <nash/nash.h>

using namespace nash;

class Looper : public Script<Object> {
public:
  std::map<Direction, bool> pressing;
  int curr, id, total;

  Looper(const std::string &name, int id, int total)
      : Script<Object>(name), id(id), total(total), curr(0) {
    // Do nothing
  }

  int mod(int a, int b) { return (a % b + b) % b; }

  void updateFromKey(Direction key, int diff) {
    if (!pressing[key]) {
      if (context->getDirectionKey(key)) {
        pressing[key] = true;
        curr = mod(curr + diff, total);
        target->setHidden(curr != id);
      }
    } else {
      if (!context->getDirectionKey(key)) {
        pressing[key] = false;
      }
    }
  }

  virtual void start() { target->setHidden(curr != id); }
};

#endif