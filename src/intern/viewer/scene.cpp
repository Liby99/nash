#include "viewer/scene.h"

using namespace nash;

Scene::Scene() : camera(), root() {
  // Do nothing
}

void Scene::setSize(int width, int height) {
  camera.setSize(width, height);
}

void Scene::start(Context & context) {
  camera.start(context);
  root.startWrapper(context);
}

void Scene::update(Context & context) {
  Matrix4f base = Matrix4f::Identity();
  camera.update(context);
  root.updateWrapper(context, base);
}

void Scene::render(Context & context) {
  Matrix4f viewPersp = camera.getViewPerspective();
  root.renderWrapper(context, viewPersp);
}
