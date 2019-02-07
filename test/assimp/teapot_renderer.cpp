#include <nash/nash.h>

using namespace nash;

int main(int argc, char * argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.camera.setController(camCtrl);

  AssimpObject teapot("./res/model/teapot.obj");
  teapot.getRootNode().getChildNode("defaultobject").getMesh("defaultobject")
    .setShader(Shader::get());
  scene.addObject(teapot);

  Viewer viewer(1280, 720, "Teapot Viewer test", scene);
  viewer.start();

  Nash::shutdown();
}
