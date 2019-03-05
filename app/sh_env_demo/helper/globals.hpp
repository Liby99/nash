#ifndef SH_ENV_GLOBALS_HPP
#define SH_ENV_GLOBALS_HPP

#include <nash/nash.h>
#include "sh_color_spheres.hpp"

using namespace nash;

std::vector<std::string> skyBoxPaths = {"./image/cubemap/room/", "./image/cubemap/gracecathedral/",
                                        "./image/cubemap/colors/", "./image/cubemap/bridge3/"};

std::vector<int> skyBoxSampleGaps = {16, 1, 1, 16};

std::vector<std::string> modelPaths = {"./model/teapot.obj", "./model/dog.obj",
                                       "./model/simp_desk.ply", "sphere", "cube"};

std::vector<std::string> skyBoxSides = {"posy.jpg", "negy.jpg", "negx.jpg",
                                        "posx.jpg", "posz.jpg", "negz.jpg"};

std::vector<Image *> images;

std::vector<CubeMap *> cubeMaps;

std::vector<SkyBox *> skyBoxes;

std::vector<SHColor *> shColors;

std::vector<SHColorSpheres *> shSpheres;

std::vector<Script<Object> *> scripts;

std::vector<Object *> objects;

int activatedSkyBox = 0;

#endif