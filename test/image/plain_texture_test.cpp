#include <nash/nash.h>

using namespace nash;

class LoadTexture : public Script<Object> {
public:
  LoadTexture(const std::string &name, Texture &texture)
      : Script<Object>(name), texture(&texture) {}

  virtual void preRender() {
    if (target->hasShader()) {
      texture->bind(1);
      target->getShader().setUniform("tex", 1);
    }
  }

private:
  Texture *texture;
};

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.camera.setController(camCtrl);

  Image image("./image/posx.jpg");
  Texture2D tex(image);
  LoadTexture loadTexture("load-texture", tex);

  Plane plane;
  plane.transform.position.y() = -0.5;
  plane.setShader(Shader::get("./shader/plain_texture"));
  plane.attachScript(loadTexture);
  scene.addObject(plane);

  Viewer viewer(1280, 720, "Plane test", scene);
  viewer.start();

  Nash::shutdown();
}
