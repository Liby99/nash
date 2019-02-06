#include <nash/nash.h>

using namespace nash;

class Toggle : public Script {
public:
  bool pressing, show;

  Toggle(const std::string & name) : Toggle(name, true) { }

  Toggle(const std::string & name, bool initial) : Script(name) {
    show = initial;
  }

  virtual void update() {
    if (!pressing) {
      if (context->getKey('a')) {
        pressing = true;
        show = !show;
        if (show) {
          object->show();
        } else {
          object->hide();
        }
      }
    } else {
      if (!context->getKey('a')) {
        pressing = false;
      }
    }
  }
};

int main() {
  nanogui::init();
  Scene scene;
  scene.camera.position << 3, 3, 3;

  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());
  Toggle cubeToggle("toggle", true);
  cube.attachScript(cubeToggle);

  Sphere sphere;
  sphere.setParent(scene.root);
  sphere.setShader(Shader::get());
  Toggle sphereToggle("toggle", false);
  sphere.attachScript(sphereToggle);

  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();
  nanogui::shutdown();
}
