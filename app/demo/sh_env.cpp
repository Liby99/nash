#include <nash/nash.h>

using namespace nash;

std::vector<std::string> skyBoxPaths = {"./image/cubemap/room/", "./image/cubemap/gracecathedral/",
                                        "./image/cubemap/colors/"};

std::vector<std::string> modelPaths = {"./model/teapot.obj", "./model/dog.obj",
                                       "./model/simp_desk.ply", "sphere", "cube"};

std::vector<std::string> skyBoxSides = {"posy.jpg", "negy.jpg", "negx.jpg",
                                        "posx.jpg", "posz.jpg", "negz.jpg"};

class Looper : public Script<Object> {
public:
  std::map<Direction, bool> pressing;
  int curr, id, total;

  Looper(const std::string &name, int id, int total)
      : Script<Object>(name), id(id), total(total), curr(0) {
    // Do nothing
  }

  int mod(int a, int b) { return (a % b + b) % b; }

  void updateFromKey(Direction key, int diff) {
    if (!pressing[key]) {
      if (context->getDirectionKey(key)) {
        pressing[key] = true;
        curr = mod(curr + diff, total);
        target->setHidden(curr != id);
      }
    } else {
      if (!context->getDirectionKey(key)) {
        pressing[key] = false;
      }
    }
  }

  virtual void start() { target->setHidden(curr != id); }
};

class SkyBoxLooper : public Looper {
public:
  SkyBoxLooper(const std::string &name, int id, int total) : Looper(name, id, total) {}

  virtual void update() {
    updateFromKey(Direction::Left, 1);
    updateFromKey(Direction::Right, -1);
  }
};

class ObjectLooper : public Looper {
public:
  ObjectLooper(const std::string &name, int id, int total) : Looper(name, id, total) {}

  virtual void update() {
    updateFromKey(Direction::Up, -1);
    updateFromKey(Direction::Down, 1);
  }
};

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  FirstPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  std::vector<Image *> images;
  std::vector<CubeMap *> cubeMaps;
  std::vector<SkyBox *> skyBoxes;
  std::vector<Script<Object> *> scripts;
  std::vector<Object *> objects;

  for (int i = 0; i < skyBoxPaths.size(); i++) {
    int off = i * 6;
    for (int j = 0; j < skyBoxSides.size(); j++) {
      images.push_back(new Image(Path::getAbsolutePathTo(skyBoxPaths[i] + skyBoxSides[j])));
    }
    cubeMaps.push_back(new CubeMap(*images[off], *images[off + 1], *images[off + 2],
                                   *images[off + 3], *images[off + 4], *images[off + 5]));
    skyBoxes.push_back(new SkyBox(*cubeMaps[i]));
    scripts.push_back(new SkyBoxLooper("looper", i, skyBoxPaths.size()));
    skyBoxes[i]->attachScript(*scripts[scripts.size() - 1]);
    scene.addObject(*skyBoxes[i]);
  }

  for (int i = 0; i < modelPaths.size(); i++) {
    if (modelPaths[i] == "sphere") {
      objects.push_back(new Sphere());
    } else if (modelPaths[i] == "cube") {
      objects.push_back(new Cube());
    } else {
      objects.push_back(new AssimpObject(Path::getAbsolutePathTo(modelPaths[i])));
    }
    scripts.push_back(new ObjectLooper("looper", i, modelPaths.size()));
    objects[i]->attachScript(*scripts[scripts.size() - 1]);
    scene.addObject(*objects[i]);
  }

  Viewer viewer(1280, 720, "SH Environment Lighting", scene);
  viewer.start();

  for (int i = 0; i < skyBoxPaths.size(); i++) {
    for (int j = 0; j < skyBoxSides.size(); j++) {
      delete images[6 * i + j];
    }
    delete cubeMaps[i];
    delete skyBoxes[i];
  }

  for (int i = 0; i < scripts.size(); i++) {
    delete scripts[i];
  }

  Nash::shutdown();
}