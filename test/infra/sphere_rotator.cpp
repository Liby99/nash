#include <nash/nash.h>

using namespace nash;

class Rotator : public Script {
public:
  int counter;
  
  Rotator(const std::string & name) : Script(name) {
    counter = 0;
  }
  
  virtual void update() {
    counter++;
    object->transform.rotation = AngleAxisf(counter * 0.01, Vector3f::UnitY());
  }
};

int main() {
  nanogui::init();
  
  Scene scene;
  scene.camera.position << 3, 3, 3;
  
  Sphere sphere;
  sphere.setParent(scene.root);
  sphere.setShader(Shader::get());
  Rotator rotator("rotator");
  sphere.attachScript(rotator);

  Viewer viewer(1280, 720, "Viewer test", scene);
  viewer.start();
  nanogui::shutdown();
}
