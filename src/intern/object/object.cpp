#include "object/object.h"

using namespace nash;

Object::Object() : transform(), active(true), shader(nullptr), parent(nullptr) {
  
}

bool Object::hasParent() {
  return parent != nullptr;
}

Object & Object::getParent() {
  return *parent;
}

void Object::setParent(Object & p) {
  this->parent = &p;
  this->parent->children.push_back(this);
}

void Object::removeFromParent() {
  std::vector<Object *> & cs = this->parent->children;
  cs.erase(std::remove(cs.begin(), cs.end(), this), cs.end());
  this->parent = nullptr;
}
