/**
 * In this example, you can press either `a` or `b` to hide/show the cube. This is a demonstration
 * of using lambda function as the toggle function instead of just using single keys. Therefore
 * you can create much more complex toggle right here.
 */

#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();

  Scene scene;
  scene.camera.position << 3, 3, 3;

  Toggle::ToggleFunction func = [](Context & context) {
    return context.getKey('a') || context.getKey('b');
  };

  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());
  Toggle cubeToggle("toggle", func);
  cube.attachScript(cubeToggle);

  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();
  nanogui::shutdown();
}
