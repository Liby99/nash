#include "helper/env_coef_binder.hpp"
#include "helper/mesh_coef_binder.hpp"
#include <nash/nash.h>

using namespace nash;

// const std::string objPath = "./model/simp_desk.ply";
const std::string objPath = "./model/teapot.obj";
// const std::string coefPath = "./coefs/obj/simp_desk.ply.coef";
const std::string shaderPath = "./shader/sh_env_shadow";
const std::string envMapPath = "./image/cubemap/colors/";
const int envMapSampleGap = 1;
const int numDegree = 4;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  // Load the model
  AssimpObject model(Path::getAbsolutePathTo(objPath));

  // Load the environment map
  Image right(Path::getAbsolutePathTo(envMapPath + "posx.jpg"));
  Image left(Path::getAbsolutePathTo(envMapPath + "negx.jpg"));
  Image top(Path::getAbsolutePathTo(envMapPath + "posy.jpg"));
  Image down(Path::getAbsolutePathTo(envMapPath + "negy.jpg"));
  Image front(Path::getAbsolutePathTo(envMapPath + "posz.jpg"));
  Image back(Path::getAbsolutePathTo(envMapPath + "negz.jpg"));
  CubeMap cubeMap(top, down, left, right, front, back);

  // Generate binders for model shadow coefs and environment map coefs
  MeshCoefBinder meshCoefBinder(numDegree, "mesh-coef-binder");
  EnvCoefBinder envCoefBinder(cubeMap, numDegree, envMapSampleGap, "env-coef-binder");

  // Get the mesh from model object and attach the binders
  AssimpMesh &mesh = *model.getMeshes()[0];
  mesh.attachScript(meshCoefBinder);
  mesh.attachScript(envCoefBinder);
  mesh.setShader(Shader::get(Path::getAbsolutePathTo(shaderPath)));

  // std::cout << "Side Length of the Mesh Coef Texture: " << meshCoefBinder.getTextureWidth() <<
  // std::endl;

  // Finally add the object to the scene
  scene.addObject(model);

  // We also add the skybox to the scene
  SkyBox skyBox(cubeMap);
  scene.addObject(skyBox);

  Viewer viewer(1280, 720, "SH Environment Shadow Demo", scene);
  viewer.start();

  Nash::shutdown();
}