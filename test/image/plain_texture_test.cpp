#include <nash/nash.h>

using namespace nash;

class LoadTexture : public Script<Object> {
public:
  LoadTexture(const std::string &name, Texture &texture) : LoadTexture(name, texture, 1) {}

  LoadTexture(const std::string &name, Texture &texture, int pos)
      : Script<Object>(name), texture(&texture), pos(pos) {}

  virtual void preRender() {
    if (target->hasShader()) {
      texture->bind(pos);
      target->getShader().setUniform("tex", pos);
    }
  }

private:
  int pos;
  Texture *texture;
};

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.camera.setController(camCtrl);

  Image bridgeImage("./image/posx.jpg");
  Image gogoImage("./image/gogo.png");
  Image headImage("./image/head.bmp");
  Texture2D bridgeTexture(bridgeImage);
  Texture2D gogoTexture(gogoImage);
  Texture2D headTexture(headImage);
  LoadTexture loadBridgeTexture("load-texture-bridge", bridgeTexture, 1);
  LoadTexture loadGogoTexture("load-texture-gogo", gogoTexture, 2);
  LoadTexture loadHeadTexture("load-texture-head", headTexture, 3);

  Plane plane;
  plane.transform.position << -1, -0.5, 0;
  plane.setShader(Shader::get("./shader/plain_texture"));
  plane.attachScript(loadBridgeTexture);
  scene.addObject(plane);

  Plane plane2;
  plane2.transform.position << 0, -0.5, 0;
  plane2.setShader(Shader::get("./shader/plain_texture"));
  plane2.attachScript(loadGogoTexture);
  scene.addObject(plane2);

  Plane plane3;
  plane3.transform.position << 1, -0.5, 0;
  plane3.setShader(Shader::get("./shader/plain_texture"));
  plane3.attachScript(loadHeadTexture);
  scene.addObject(plane3);

  Viewer viewer(1280, 720, "Plane test", scene);
  viewer.start();

  Nash::shutdown();
}
