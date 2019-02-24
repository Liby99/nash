#include <nash/nash.h>

using namespace nash;

const int SAMPLE_AMOUNT = 10000;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  Image right("./image/cubemap/room/posx.jpg");
  Image left("./image/cubemap/room/negx.jpg");
  Image top("./image/cubemap/room/posy.jpg");
  Image down("./image/cubemap/room/negy.jpg");
  Image front("./image/cubemap/room/posz.jpg");
  Image back("./image/cubemap/room/negz.jpg");
  CubeMap cubeMap(top, down, left, right, front, back);

  SkyBox skybox(cubeMap);
  Toggle toggle("toggle", 't');
  skybox.attachScript(toggle);
  scene.addObject(skybox);

  std::vector<Vector3f> samples(SAMPLE_AMOUNT);
  Sampler::sampleSphere(samples);

  std::vector<Vector4u> colors(SAMPLE_AMOUNT);
  for (int i = 0; i < SAMPLE_AMOUNT; i++) {
    colors[i] = cubeMap.getColor(samples[i]);
  }

  ColoredPointCloud cloud(samples, colors);
  scene.addObject(cloud);

  Viewer viewer(1280, 720, "Samples Visualizer", scene);
  viewer.start();

  Nash::shutdown();
}