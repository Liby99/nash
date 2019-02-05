#include <nash/nash.h>

using namespace nash;

class Rotator : public Script {
public:
  int counter = 0;
  Rotator(const std::string & name) : Script(name) {}
  virtual void update() {
    counter++;
    object->transform.rotation = AngleAxisf(counter * 0.01, Vector3f::UnitY());
  }
};

int main() {
  nanogui::init();
  Scene scene;
  scene.camera.position << 3, 3, 3;
  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());

  // ========   ATTENTION   ======== //
  Rotator rotator("rotator");
  cube.attachScript(rotator);
  // ======== END ATTENTION ======== //

  Viewer viewer(1280, 720, "Viewer test", scene);
  viewer.start();
  nanogui::shutdown();
}
