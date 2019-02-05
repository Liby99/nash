#include "utility/script.h"

using namespace nash;

Script::Script(const std::string & name) : name(name) {
  // Do Nothing
}

void Script::bind(Object * obj) {
  object = obj;
}

void Script::start() {
  // Do Nothing
}

void Script::update() {
  // Do Nothing
}
