/**
 * TEST FAILING. DON'T RELY ON THIS.
 */

#include "helpers/looper.hpp"
#include <nash/nash.h>

using namespace nash;

const std::string directory = "./image/colors/";
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
  mat.row(0) << c1 * l.get(2, 2), c1 * l.get(2, -2), c1 * l.get(2, 1), c2 * l.get(1, 1);
  mat.row(1) << c1 * l.get(2, -2), -c1 * l.get(2, 2), c1 * l.get(2, -1), c2 * l.get(1, -1);
  mat.row(2) << c1 * l.get(2, 1), c1 * l.get(2, -1), c3 * l.get(2, 0), c2 * l.get(1, 0);
  mat.row(3) << c2 * l.get(1, 1), c2 * l.get(1, -1), c2 * l.get(1, 0),
      c4 * l.get(0, 0) - c5 * l.get(2, 0);
  // mat.row(0) << l.get(0, 0), l.get(1, 1), l.get(2, 2), l.get(3, 3);
  // mat.row(1) << l.get(1, -1), l.get(1, 0), l.get(2, 1), l.get(3, 2);
  // mat.row(2) << l.get(2, -2), l.get(2, -1), l.get(2, 0), l.get(3, 1);
  // mat.row(3) << l.get(3, -3), l.get(3, -2), l.get(3, -1), l.get(3, 0);
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

  SkyBoxSHCalculator calc(cubeMap, 4);
  const std::vector<SHCoefs *> &list = calc.getCoefsList();
  SHCoefs &red = *list[0], &green = *list[1], &blue = *list[2];
  Matrix4f redCoefs, greenCoefs, blueCoefs;
  loadCoefsMatrix(red, redCoefs);
  loadCoefsMatrix(green, greenCoefs);
  loadCoefsMatrix(blue, blueCoefs);

  std::cout << redCoefs << std::endl;

  AssimpObject model(modelFile);
  AssimpMesh &mesh = *model.getMeshes()[0];
  mesh.setShader(Shader::get("./shader/env_shading"));
  EnvShading setEnv("set-env", redCoefs, greenCoefs, blueCoefs);
  mesh.attachScript(setEnv);
  Looper loopMesh("looper", 0, 4);
  mesh.attachScript(loopMesh);
  scene.addObject(model);

  SHSphere redSphere(red);
  Looper loopRed("looper", 1, 4);
  redSphere.attachScript(loopRed);
  scene.addObject(redSphere);

  SHSphere greenSphere(green);
  Looper loopGreen("looper", 2, 4);
  greenSphere.attachScript(loopGreen);
  scene.addObject(greenSphere);

  SHSphere blueSphere(blue);
  Looper loopBlue("looper", 3, 4);
  blueSphere.attachScript(loopBlue);
  scene.addObject(blueSphere);

  Viewer viewer(1280, 720, "Environment Shading Test", scene);
  viewer.start();

  Nash::shutdown();
}