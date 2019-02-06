/**
 * In this example you can see how we are using Script to make the cube movable by `wasd`
 * interaction method
 */

#include <nash/nash.h>

using namespace nash;

class Mover : public Script {
public:
  static constexpr float SPEED = 0.05;

  Mover(const std::string & name) : Script(name) { }

  void update() {
    Vector3f diff(0, 0, 0);
    if (context->getKey('w')) {
      diff.y() += SPEED;
    }
    if (context->getKey('a')) {
      diff.x() -= SPEED;
    }
    if (context->getKey('s')) {
      diff.y() -= SPEED;
    }
    if (context->getKey('d')) {
      diff.x() += SPEED;
    }
    object->transform.position += diff;
  }
};

int main() {
  nanogui::init();

  Scene scene;
  scene.camera.position << 1, 1, 5;

  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());
  Mover mover("mover");
  cube.attachScript(mover);

  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();
  nanogui::shutdown();
}
