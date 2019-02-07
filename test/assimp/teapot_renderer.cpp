#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();
  
  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.camera.setController(camCtrl);
  
  Cube cube;
  cube.setShader(Shader::get());
  // scene.addObject(cube);
  
  AssimpObject teapot("./res/teapot.obj");
  teapot.getRootNode().getNode("defaultobject").getMesh("defaultobject").setShader(Shader::get());
  scene.addObject(teapot);
  
  Viewer viewer(1280, 720, "Teapot Viewer test", scene);
  viewer.start();
  
  nanogui::shutdown();
}
