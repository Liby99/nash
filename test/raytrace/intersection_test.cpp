
#include <chrono>
#include <nash/nash.h>
#include <omp.h>

using namespace nash;

class ColoredMesh : public Mesh {
public:
  ColoredMesh(const AssimpMesh &assimpMesh, const MatrixXf &color) : Mesh(),
                                                                     color(
                                                                         color) {
    positions = assimpMesh.getPositions();
    normals = assimpMesh.getNormals();
    indices = assimpMesh.getIndices();
    setShader(Shader::get("F:/users/DESKTOP/Documents/GitHub/nash/res/shader"
                          "/plain_color"));
  }

  ~ColoredMesh() {

  }

  virtual void render() {
    shader->uploadAttr("color", color);
    Mesh::render();
  }

private:
  MatrixXf color;
};

int main(int argc, char *argv[]) {
  // simple triangle
  Triangle t({Vector3f(0, 0, 0), Vector3f(0, 0, 3), Vector3f(3, 0, 0)});
  Ray *tr = new Ray(Vector3f(1, 1, 1), Vector3f(-0.5, -1, -0.5));
  Intersection tintersection(*tr);
  bool tresult = t.intersect(*tr, tintersection);

  // simple box
  BoundingBox b({Vector3f(0, 0, 0), Vector3f(1, 1, 1)});
  Ray *br = new Ray(Vector3f(0.5, 0.5, 0.5), Vector3f(1, 1, 1));
  Intersection bintersection(*br);
  bool bresult = b.intersect(*br, bintersection);

  // an .obj mesh
  AssimpObject teapot(
      "F:/users/DESKTOP/Documents/GitHub/nash/res/model/teapot.obj");
  const AssimpMesh &mesh = *(teapot.getMeshes()[0]);
  std::cerr << "Start" << std::endl;
  auto start = std::chrono::system_clock::now();
  BoxTreeMesh *teapotBTMesh = new BoxTreeMesh(mesh);

  std::vector<Vector3f> samples(100);
  Sampler::sampleSphere(samples);

  std::cerr << "Iteration:" << mesh.getPositions().cols() << std::endl;

  MatrixXf color(3, mesh.getPositions().cols());

#ifdef BRUTEFORCE
  std::vector<Triangle*> tris;
  for(int i = 0 ; i < mesh.getIndices().cols(); i ++){
    Vector3u currInd = mesh.getIndices().col(i);
    tris.push_back(new Triangle(mesh.getPositions().col(currInd[0]),
                    mesh.getPositions().col(currInd[1]),
                    mesh.getPositions().col(currInd[2])));
  }
#endif

#pragma omp parallel for
  for (int i = 0; i < mesh.getPositions().cols(); i++) {
    int count = 0;
    Vector3f currPos = mesh.getPositions().col(i);
    for (int j = 0; j < samples.size(); j++) {
      Ray ray(currPos, samples[j]);
      ray.step();
      Intersection intersection1(ray);
#ifdef BRUTEFORCE
      for(int k = 0; k < tris.size(); k ++) {
        tris[k]->intersect(ray, intersection1);
      }
#else
      bool result = teapotBTMesh->intersect(ray, intersection1);
#endif
      if (intersection1.hit) {
        // TODO: if intersect
        count++;
      } else {
      }
    }
    float percent = (float) count / samples.size();
    // TODO: delete this when finalized
    // std::cerr << percent << std::endl;
    color.col(i) = Vector3f(1 - percent, 1 - percent, 1 - percent);
    // TODO: delete this when finalized
    // fprintf(stderr, "Current point is:(%f,%f,%f); The percentage of "
    //                "intersections is: %f%% \n", currPos[0], currPos[1],
    //                currPos[2], (float)count/samples.size() * 100);
  }

  auto end = std::chrono::system_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
      end - start);
  std::cerr << elapsed.count() << '\n';

  Nash::init(argc, argv);

  Scene scene;
  ThirdPersonCamera camCtrl;
  scene.camera.setController(camCtrl);

  ColoredMesh coloredMesh(*teapot.getMeshes()[0], color);
  scene.addObject(coloredMesh);

  Viewer viewer(1280, 720, "Intersection test", scene);
  viewer.start();

  Nash::shutdown();
}