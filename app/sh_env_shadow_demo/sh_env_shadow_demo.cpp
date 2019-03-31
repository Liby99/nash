#include "helper/env_coef_binder.hpp"
#include "helper/mesh_coef_binder.hpp"
#include <nash/nash.h>

using namespace nash;

const std::string objPath = "./model/teapot.obj";
const std::string coefPath = "./coefs/teapot.obj.defaultobject.coef";
const std::string shaderPath = "./shader/sh_env_shadow";
const std::string envMapPath = "./image/cubemap/room/";
const int envMapSampleGap = 16;
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
  std::string coefAbsPath = Path::getAbsolutePathTo(coefPath);
  std::cout << coefAbsPath << std::endl;
  MeshCoefBinder meshCoefBinder(coefAbsPath, numDegree, "mesh-coef-binder");
  EnvCoefBinder envCoefBinder(cubeMap, numDegree, envMapSampleGap, "env-coef-binder");

  // Get the mesh from model object and attach the binders
  AssimpMesh &mesh = *model.getMeshes()[0];
  mesh.attachScript(meshCoefBinder);
  mesh.attachScript(envCoefBinder);
  mesh.setShader(Shader::get(Path::getAbsolutePathTo(shaderPath)));

  // Finally add the object to the scene
  scene.addObject(model);

  // We also add the skybox to the scene
  SkyBox skyBox(cubeMap);
  scene.addObject(skyBox);

  Viewer viewer(1280, 720, "SH Environment Shadow Demo", scene);
  viewer.start();

  Nash::shutdown();
}