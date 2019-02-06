/**
 * In this example you can use `wasd` to move your self around, use space (' ') to move yourself
 * upward, and use `x` to move yourself downward. You can also use your mouse to rotate, and scroll
 * wheel to move yourself toward or away from the target. We placed three cubes in the scene to let
 * you get a precise sense of travelling.
 *
 * Note that we only need to attach the `ThirdPersonCamera` script to the camera to get this effect.
 * `ThirdPersonCamera` is inherited from `Script<Camera>`
 */

#include <nash/nash.h>

using namespace nash;

int main() {
  nanogui::init();

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.camera.setController(camCtrl);

  Cube cube;
  cube.setParent(scene.root);
  cube.setShader(Shader::get());

  Cube cube2;
  cube2.transform.scale << 0.5, 0.5, 0.5;
  cube2.transform.position << -2, -1.2, 1.4;
  cube2.setParent(scene.root);
  cube2.setShader(Shader::get());

  Viewer viewer(1280, 720, "Cube test", scene);
  viewer.start();
  nanogui::shutdown();
}
