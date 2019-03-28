#include "../helper/coef_texture.hpp"
#include "../helper/mesh_coef_binder.hpp"
#include <nash/nash.h>

using namespace nash;

const std::string objPath = "../model/teapot.obj";
const std::string coefPath = "../coefs/obj/simp_desk.ply.coef";
const std::string shaderPath = "../shader/coef_texture";

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  AssimpObject model(Path::getAbsolutePathTo(objPath));
  MeshCoefBinder binder(4, "mesh-coef-binder");
  model.getMeshes()[0]->attachScript(binder);

  Plane plane;
  CoefTexture coefTexture(binder.getTexture(), binder.getTextureWidth(), "plane-texture");
  plane.setShader(Shader::get(Path::getAbsolutePathTo(shaderPath)));
  plane.attachScript(coefTexture);
  scene.addObject(plane);

  Viewer viewer(1280, 720, "Mesh Coefficient Texture Viewer", scene);
  viewer.start();

  Nash::shutdown();
}