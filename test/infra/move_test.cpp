/**
 * In this example you can see how we are using Script to make the cube movable
 * by `wasd` interaction method
 */

#include <nash/nash.h>

using namespace nash;

class Mover : public Script<Object> {
public:
  static constexpr float SPEED = 0.05;

  Mover(const std::string &name) : Script(name) {}

  void update() {
    Vector3f diff(0, 0, 0);
    if (context->getKey('w'))
      diff.y() += SPEED;
    if (context->getKey('a'))
      diff.x() -= SPEED;
    if (context->getKey('s'))
      diff.y() -= SPEED;
    if (context->getKey('d'))
      diff.x() += SPEED;
    target->transform.position += diff;
  }
};

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  scene.getCamera().position << 1, 1, 5;

  Cube cube;
  Mover mover("mover");
  cube.attachScript(mover);
  scene.addObject(cube);

  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();

  Nash::shutdown();
}