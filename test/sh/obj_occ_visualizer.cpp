#include <chrono>
#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  AssimpObject desk("./model/simp_desk.ply");
  desk.transform.rotation = AngleAxisf(-PI / 2, Vector3f(1, 0, 0));
  scene.addObject(desk);

  // Time
  auto start = std::chrono::system_clock::now();

  AssimpMesh &mesh = *(desk.getMeshes()[0]);
  MeshSHCalculator calc(mesh, 8);
  auto coefsList = calc.getCoefsList();
  SHSphere *shSpheres[coefsList.size()];
  for (int i = 0; i < coefsList.size(); i++) {
    SHSphere *coefSphere = new SHSphere(*coefsList[i]);
    coefSphere->transform.position = mesh.getPositions().col(i);
    coefSphere->transform.scale << 0.01, 0.01, 0.01;
    coefSphere->setParent(desk);
    shSpheres[i] = coefSphere;
  }

  // Time
  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cerr << elapsed.count() << '\n';

  Viewer viewer(1280, 720, "Simple Desk SH", scene);
  viewer.start();

  Nash::shutdown();

  for (int i = 0; i < coefsList.size(); i++) {
    delete shSpheres[i];
  }
}