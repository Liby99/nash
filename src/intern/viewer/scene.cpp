#include "viewer/scene.h"

using namespace nash;

Scene::Scene() : camera(), root() {
  // Do nothing
}

void Scene::setSize(int width, int height) {
  camera.setSize(width, height);
}

void Scene::start() {
  root.startWrapper();
}

void Scene::update() {
  Matrix4f base = Matrix4f::Identity();
  root.updateWrapper(base);
}

void Scene::render() {
  Matrix4f viewPersp = camera.getViewPerspective();
  root.renderWrapper(viewPersp);
}
