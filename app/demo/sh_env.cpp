#include "helper/coefs_updator.hpp"
#include "helper/globals.hpp"
#include "helper/object_looper.hpp"
#include "helper/set_sh_coefs.hpp"
#include "helper/sky_box_looper.hpp"

void loadImages() {
  for (int i = 0; i < skyBoxPaths.size(); i++) {

    // First load the images
    for (int j = 0; j < skyBoxSides.size(); j++) {
      images.push_back(new Image(Path::getAbsolutePathTo(skyBoxPaths[i] + skyBoxSides[j])));
    }

    // Generate cubemap from the images
    int off = i * 6;
    cubeMaps.push_back(new CubeMap(*images[off], *images[off + 1], *images[off + 2],
                                   *images[off + 3], *images[off + 4], *images[off + 5]));
  }
}

void loadObjects() {
  for (int i = 0; i < modelPaths.size(); i++) {
    if (modelPaths[i] == "sphere") {
      objects.push_back(new Sphere());
    } else if (modelPaths[i] == "cube") {
      objects.push_back(new Cube());
    } else {
      objects.push_back(new AssimpObject(Path::getAbsolutePathTo(modelPaths[i])));
    }
  }
}

void load() {
  loadImages();
  loadObjects();
}

void computeEnvCoefs() {
  for (int i = 0; i < cubeMaps.size(); i++) {
    calculators.push_back(new SkyBoxSHCalculator(*cubeMaps[i], 10, skyBoxSampleGaps[i]));
  }
}

void cleanImages() {
  for (int i = 0; i < skyBoxPaths.size(); i++) {
    for (int j = 0; j < skyBoxSides.size(); j++) {
      delete images[6 * i + j];
    }
    delete cubeMaps[i];
    delete skyBoxes[i];
  }
}

void cleanCalculators() {
  for (int i = 0; i < calculators.size(); i++) {
    delete calculators[i];
  }
}

void cleanObjects() {
  for (int i = 0; i < objects.size(); i++) {
    delete objects[i];
  }
  for (int i = 0; i < shColors.size(); i++) {
    delete shColors[i];
  }
}

void cleanScripts() {
  for (int i = 0; i < scripts.size(); i++) {
    delete scripts[i];
  }
}

void clean() {
  cleanImages();
  cleanCalculators();
  cleanObjects();
  cleanScripts();
}

int main(int argc, char *argv[]) {
  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.getCamera().setController(camCtrl);

  load(); // Skyboxes will be filled with sky boxes, objects will be filled with objects

  // Add the environment maps into the scene
  for (int i = 0; i < cubeMaps.size(); i++) {
    skyBoxes.push_back(new SkyBox(*cubeMaps[i]));
    scripts.push_back(new SkyBoxLooper("looper", i, cubeMaps.size()));
    skyBoxes[i]->attachScript(*scripts[scripts.size() - 1]);
    scene.addObject(*skyBoxes[i]);
  }

  computeEnvCoefs(); // Start to compute the coefficients from environment maps

  // Add the coefficient spheres into the scene
  for (int i = 0; i < cubeMaps.size(); i++) {
    std::vector<SHCoefs *> list = calculators[i]->getCoefsList();
    shColors.push_back(new SHColorSpheres(*list[0], *list[1], *list[2]));
    scripts.push_back(new SkyBoxLooper("looper", i, cubeMaps.size()));
    shColors[i]->attachScript(*scripts[scripts.size() - 1]);
    shColors[i]->transform.position.z() += 1;
    scene.addObject(*shColors[i]);
  }

  // Add the objects into the scene
  Shader &shEnvShader = Shader::get(Path::getAbsolutePathTo("./shader/sh_env"));
  for (int i = 0; i < objects.size(); i++) {

    // Add looper script
    ObjectLooper *looper = new ObjectLooper("looper", i, objects.size());
    objects[i]->attachScript(*looper);

    // Add sh setter script
    CoefsUpdator *updator = new CoefsUpdator("updator");
    objects[i]->attachScript(*updator);

    // Add sh coefs setter
    SetSHCoefs *setter = new SetSHCoefs("setter", 4);
    objects[i]->attachScript(*setter);

    // Add the above scripts to the `scripts` vector
    scripts.push_back(looper);
    scripts.push_back(updator);
    scripts.push_back(setter);

    // Finally add the object to the scene
    objects[i]->setShader(shEnvShader);
    scene.addObject(*objects[i]);
  }

  Viewer viewer(1280, 720, "SH Environment Lighting", scene);
  viewer.start();

  clean(); // All loaded images, objects, and scripts will be freed

  Nash::shutdown();
}