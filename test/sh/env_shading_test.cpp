/**
 * TEST FAILING. DON'T RELY ON THIS.
 */

#include "helpers/looper.hpp"
#include <nash/nash.h>

using namespace nash;

const std::string directory = "./image/cubemap/gracecathedral/";
const std::string modelFile = "./model/teapot.obj";

const float c1 = 0.429043;
const float c2 = 0.511664;
const float c3 = 0.743125;
const float c4 = 0.886227;
const float c5 = 0.247708;

class EnvShading : public Script<Object> {
public:
  EnvShading(const std::string &name, const Matrix4f &r, const Matrix4f &g, const Matrix4f &b)
      : Script<Object>(name), red(r), green(g), blue(b) {}

  virtual void preRender() {
    target->getShader().setUniform("redCoefs", red);
    target->getShader().setUniform("greenCoefs", green);
    target->getShader().setUniform("blueCoefs", blue);
  }

private:
  const Matrix4f &red, &green, &blue;
};

/**
 * Ravi et al. An Efficient Representation for Irradiance Environment Maps, page 3, section 3.2
 */
void loadCoefsMatrix(const SHCoefs &l, Matrix4f &mat) {
  // mat.row(0) << c1 * l.get(2, 2), c1 * l.get(2, -2), c1 * l.get(2, 1), c2 * l.get(1, 1);
  // mat.row(1) << c1 * l.get(2, -2), -c1 * l.get(2, 2), c1 * l.get(2, -1), c2 * l.get(1, -1);
  // mat.row(2) << c1 * l.get(2, 1), c1 * l.get(2, -1), c3 * l.get(2, 0), c2 * l.get(1, 0);
  // mat.row(3) << c2 * l.get(1, 1), c2 * l.get(1, -1), c2 * l.get(1, 0),
  //     c4 * l.get(0, 0) - c5 * l.get(2, 0);
  // mat << l.get(0, 0), l.get(1, 1), l.get(2, 2), l.get(3, 3),
  //        l.get(1, -1), l.get(1, 0), l.get(2, 1), l.get(3, 2),
  //        l.get(2, -2), l.get(2, -1), l.get(2, 0), l.get(3, 1),
  //        l.get(3, -3), l.get(3, -2), l.get(3, -1), l.get(3, 0);
  mat.row(0) << c1 * l.get(2, 2), c1 * l.get(2, -2), c1 * l.get(2, 1), c2 * l.get(1, 1);
  mat.row(1) << c1 * l.get(2, -2), -c1 * l.get(2, 2), c1 * l.get(2, -1), c2 * l.get(1, -1);
  mat.row(2) << c1 * l.get(2, 1), c1 * l.get(2, -1), c3 * l.get(2, 0), c2 * l.get(1, 0);
  mat.row(3) << c2 * l.get(1, 1), c2 * l.get(1, -1), c2 * l.get(1, 0),
      c4 * l.get(0, 0) - c5 * l.get(2, 0);
}

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  Image right(directory + "posx.jpg");
  Image left(directory + "negx.jpg");
  Image top(directory + "posy.jpg");
  Image down(directory + "negy.jpg");
  Image front(directory + "posz.jpg");
  Image back(directory + "negz.jpg");
  CubeMap cubeMap(top, down, left, right, front, back);

  SkyBox skybox(cubeMap);
  scene.addObject(skybox);

  SkyBoxSHCalculator calc(cubeMap, 3);
  const std::vector<SHCoefs *> &list = calc.getCoefsList();
  SHCoefs &red = *list[0], &green = *list[1], &blue = *list[2];

  // BEGIN TEMP
  red.set(0, 0, 0.79);
  red.set(1, -1, 0.39);
  red.set(1, 0, -.34);
  red.set(1, 1, -.29);
  red.set(2, -2, -.11);
  red.set(2, -1, -.26);
  red.set(2, 0, -.16);
  red.set(2, 1, 0.56);
  red.set(2, 2, 0.21);
  green.set(0, 0, 0.44);
  green.set(1, -1, 0.35);
  green.set(1, 0, -.18);
  green.set(1, 1, -.06);
  green.set(2, -2, -.05);
  green.set(2, -1, -.22);
  green.set(2, 0, -.09);
  green.set(2, 1, 0.21);
  green.set(2, 2, -0.05);
  blue.set(0, 0, 0.54);
  blue.set(1, -1, 0.60);
  blue.set(1, 0, -.27);
  blue.set(1, 1, 0.01);
  blue.set(2, -2, -.12);
  blue.set(2, -1, -.47);
  blue.set(2, 0, -.15);
  blue.set(2, 1, .14);
  blue.set(2, 2, -.30);
  // END TEMP

  Matrix4f redCoefs, greenCoefs, blueCoefs;
  loadCoefsMatrix(red, redCoefs);
  loadCoefsMatrix(green, greenCoefs);
  loadCoefsMatrix(blue, blueCoefs);

  EnvShading setEnv("set-env", redCoefs, greenCoefs, blueCoefs);

  AssimpObject model(modelFile);
  AssimpMesh &mesh = *model.getMeshes()[0];
  mesh.setShader(Shader::get("./shader/env_shading"));
  mesh.attachScript(setEnv);
  Looper loopMesh("looper", 0, 5);
  mesh.attachScript(loopMesh);
  scene.addObject(model);

  Sphere sphere;
  sphere.setShader(Shader::get("./shader/env_shading"));
  sphere.attachScript(setEnv);
  Looper loopSphere("looper", 1, 5);
  sphere.attachScript(loopSphere);
  scene.addObject(sphere);

  SHSphere redSphere(red);
  Looper loopRed("looper", 2, 5);
  redSphere.attachScript(loopRed);
  scene.addObject(redSphere);

  SHSphere greenSphere(green);
  Looper loopGreen("looper", 3, 5);
  greenSphere.attachScript(loopGreen);
  scene.addObject(greenSphere);

  SHSphere blueSphere(blue);
  Looper loopBlue("looper", 4, 5);
  blueSphere.attachScript(loopBlue);
  scene.addObject(blueSphere);

  Viewer viewer(1280, 720, "Environment Shading Test", scene);
  viewer.start();

  Nash::shutdown();
}