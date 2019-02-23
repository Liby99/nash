#include <nash/nash.h>

using namespace nash;

const int GAP = 5;

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  camCtrl.incline = PI / 4;
  scene.getCamera().setController(camCtrl);

  Image negx("./image/cubemap/room/negx.jpg");
  Image posx("./image/cubemap/room/posx.jpg");
  Image negy("./image/cubemap/room/negy.jpg");
  Image posy("./image/cubemap/room/posy.jpg");
  Image negz("./image/cubemap/room/negz.jpg");
  Image posz("./image/cubemap/room/posz.jpg");
  CubeMap cubeMap(posy, negy, negx, posx, posz, negz);

  std::vector<Vector3f> positions;
  std::vector<Vector4u> colors;

  for (CubeMap::Face face : CubeMap::FACES) {
    const Image &img = cubeMap.getImage(face);
    for (int i = 0; i < img.width; i += GAP) {
      for (int j = 0; j < img.height; j += GAP) {
        float fi = (float)i / img.width - 0.5;
        float fj = -(float)j / img.height + 0.5;
        Vector4u color = img.getColor(i, j);
        Vector3f dir(0, 0, 0);
        switch (face) {
        case CubeMap::Face::Top:
          dir << fi, 0.5, fj;
          break;
        case CubeMap::Face::Down:
          dir << fi, -0.5, -fj;
          break;
        case CubeMap::Face::Right:
          dir << 0.5, fj, fi;
          break;
        case CubeMap::Face::Left:
          dir << -0.5, fj, -fi;
          break;
        case CubeMap::Face::Front:
          dir << fi, fj, -0.5;
          break;
        case CubeMap::Face::Back:
          dir << -fi, fj, 0.5;
          break;
        }
        dir.normalize();
        positions.push_back(dir);
        colors.push_back(color);
      }
    }
  }

  ColoredPointCloud pc(positions, colors);
  scene.addObject(pc);

  Viewer viewer(1280, 720, "Skybox Test", scene);
  viewer.start();

  Nash::shutdown();
}