#include <nash/nash.h>

using namespace nash;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  std::vector<Vector3f> samples(1000);
  Sampler::sampleHemiSphere(samples, Vector3f(0, 1, 0));

  PointCloud cloud(samples);
  scene.addObject(cloud);

  Viewer viewer(1280, 720, "Samples Visualizer", scene);
  viewer.start();

  Nash::shutdown();
}