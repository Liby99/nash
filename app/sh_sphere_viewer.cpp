#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();

  Scene scene;
  ThirdPersonCamera ctrl;
  scene.camera.setController(ctrl);

  std::vector<SHSphere *> spheres;
  std::vector<Rotator *> rotators;

  int n = 5;
  for (int l = 0; l < n; l++) {
    for (int m = -l; m <= l; m++) {
      SHSphere * sphere = new SHSphere(l, m);
      sphere->setParent(scene.root);
      sphere->setShader(Shader::get());
      sphere->transform.position = Vector3f(m * 0.8, 2 - l * 0.8, 0);
      sphere->transform.scale = Vector3f(0.6, 0.6, 0.6);
      Rotator * rotator = new Rotator("rotator", 0.01, Vector3f(1, 1, 1).normalized());
      sphere->attachScript(*rotator);
      spheres.push_back(sphere);
      rotators.push_back(rotator);
    }
  }

  Viewer viewer(1280, 720, "Spherical Harmonics Spheres Viewer", scene);
  viewer.start();

  for (int i = 0; i < spheres.size(); i++) {
    delete spheres[i];
    delete rotators[i];
  }

  nanogui::shutdown();
}
