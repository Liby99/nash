
#include <nash/nash.h>

using namespace nash;

int main() {
  // simple triangle
  Triangle t({Vector3f(0, 0, 0), Vector3f(0, 0, 3), Vector3f(3, 0, 0)});
  Ray *r = new Ray(Vector3f(1, 1, 1), Vector3f(-0.5, -1, -0.5));
  Intersection intersection(*r);
  bool result = t.intersect(*r, intersection);

  // an .obj mesh
  AssimpObject teapot("F:/users/DESKTOP/Documents/GitHub/nash/res/model"
                      "/teapot.obj");
  const AssimpMesh & mesh = *(teapot.getMeshes()[0]);
  BoxTreeMesh * teapotBTMesh = new BoxTreeMesh(mesh);

  std::vector<Vector3f> samples(50);
  Sampler::sampleSphere(samples);
  for(int i = 0; i < mesh.getPositions().cols(); i++){
    int count = 0;
    Vector3f currPos = mesh.getPositions().col(i);
    //Vector3f currNorm = mesh.getNormals().col(i);
    for(int j = 0; j < samples.size(); j ++){
      Ray ray(currPos, samples[j]);
      ray.step();
      Intersection intersection1(ray);
      bool result = teapotBTMesh->intersect(ray, intersection1);
      if(result){
        // TODO: if intersect
        count ++;
      }else{

      }
    }
    fprintf(stderr, "Current point is:(%f,%f,%f); The percentage of "
                    "intersections is: %f%% \n", currPos[0], currPos[1],
                    currPos[2], (float)count/samples.size() * 100);
  }
}