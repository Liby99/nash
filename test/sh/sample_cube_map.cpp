#include <nash/nash.h>

using namespace nash;

const int SAMPLE_AMOUNT = 10000;

const std::string directory = "./image/cubemap/room/";

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  Image right(Path::getAbsolutePathTo(directory + "posx.jpg"));
  Image left(Path::getAbsolutePathTo(directory + "negx.jpg"));
  Image top(Path::getAbsolutePathTo(directory + "posy.jpg"));
  Image down(Path::getAbsolutePathTo(directory + "negy.jpg"));
  Image front(Path::getAbsolutePathTo(directory + "posz.jpg"));
  Image back(Path::getAbsolutePathTo(directory + "negz.jpg"));
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