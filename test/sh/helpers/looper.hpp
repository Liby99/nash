#include <nash/nash.h>

using namespace nash;

class Looper : public Script<Object> {
public:
  bool pressing;
  int curr, id, total;

  Looper(const std::string &name, int id, int total)
      : curr(0), id(id), total(total), Script<Object>(name) {}

  virtual void start() {
    if (curr == id) {
      this->target->show();
    } else {
      this->target->hide();
    }
  }

  virtual void update() {
    if (!pressing) {
      if (context->getKey('e')) {
        pressing = true;
        curr = (curr + 1) % total;
        if (curr == id) {
          std::cout << "Showing id " << curr << std::endl;
          this->target->show();
        } else {
          this->target->hide();
        }
      }
    } else {
      if (!context->getKey('e')) {
        pressing = false;
      }
    }
  }
};