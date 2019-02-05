#include "object/object.h"

using namespace nash;

Object::Object() :
  active(true),
  shader(nullptr),
  parent(nullptr) {
  // Do nothing
}

bool Object::hasParent() {
  return parent != nullptr;
}

Object & Object::getParent() {
  return *parent;
}

void Object::setParent(Object & p) {
  if (parent != nullptr) {
    removeFromParent();
  }
  parent = &p;
  parent->children.push_back(this);
}

void Object::removeFromParent() {
  if (parent != nullptr) {
    std::vector<Object *> & cs = parent->children;
    cs.erase(std::remove(cs.begin(), cs.end(), this), cs.end());
    parent = nullptr;
  }
}

std::vector<Object *> & Object::getChildren() {
  return children;
}

Object & Object::getChild(int i) {
  return *(children[i]);
}

bool Object::hasShader() {
  return shader != nullptr;
}

Shader & Object::getShader() {
  return *shader;
}

void Object::setShader(Shader & s) {
  shader = &s;
}

void Object::activate() {
  setActive(true);
}

void Object::deactivate() {
  setActive(false);
}

void Object::setActive(bool a) {
  active = a;
}

bool Object::isActive() {
  return active;
}

void Object::start() {
  // Do nothing
}

void Object::update() {
  // Do nothing
}

void Object::render() {
  // Do nothing
}

void Object::startWrapper() {
  start();
  for (int i = 0; i < children.size(); i++) {
    children[i]->startWrapper();
  }
}

void Object::updateWrapper(Matrix4f & world) {
  if (active) {
    transform.world = world;
    Matrix4f currTransform = transform.getTransform();
    update();
    for (int i = 0; i < children.size(); i++) {
      children[i]->updateWrapper(currTransform);
    }
  }
}

void Object::renderWrapper(Matrix4f & viewPersp) {
  if (active) {
    if (hasShader()) {
      shader->bind();
      shader->setUniform("model", transform.getTransform());
      shader->setUniform("viewPersp", viewPersp);
      render();
    }
    for (int i = 0; i < children.size(); i++) {
      children[i]->renderWrapper(viewPersp);
    }
  }
}
