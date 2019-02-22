#include "adhoc/sh/mesh_sh_calculator.h"
#include "adhoc/raytrace/box_tree_mesh.h"
#include "utility/sampler.h"

using namespace nash;

const int MeshSHCalculator::SAMPLE_COUNT = 50;

MeshSHCalculator::MeshSHCalculator(const Mesh &mesh, int numDegree)
    : mesh(mesh), numDegree(numDegree) {

  // First initiate coefficient list
  coefsList = std::vector<SHCoefs *>(mesh.getPositions().cols());

  // Then generate box tree out from mesh
  BoxTreeMesh boxTree(mesh);

  float factor = 2 * PI / SAMPLE_COUNT; // Area = 2 * PI, since sampling hemisphere

// Do raytracing on the box tree
#pragma omp parallel for
  for (int i = 0; i < mesh.getPositions().cols(); i++) {

    // For each point, generate 100 samples, and also generate a corresponding coef
    Vector3f pos = mesh.getPositions().col(i);
    Vector3f norm = mesh.getNormals().col(i);
    std::vector<Vector3f> samples(SAMPLE_COUNT);
    Sampler::sampleHemiSphere(samples, norm);
    SHCoefs *coefs = new SHCoefs(numDegree);

    // Loop through all the samples
    for (int j = 0; j < samples.size(); j++) {

      // Get the theta and phi representation
      Vector2f thetaPhi = Math::normalCartToPolar(samples[j]);
      float theta = thetaPhi.x(), phi = thetaPhi.y();

      // Calculate the cosine term
      float hs = norm.dot(samples[j]); // name `hs` using the paper's definition

      // Generatea ray and do intersection test with the mesh itself
      Ray ray(pos, samples[j]);
      ray.step();
      Intersection itsct(ray);
      bool hit = boxTree.intersect(ray, itsct);

      // If not occluded by self, then add up the corresponding sh coefs
      if (!hit) {
        for (int l = 0; l < numDegree; l++) {
          for (int m = -l; m <= l; m++) {
            coefs->accumulate(l, m, hs * SH::y(l, m, theta, phi));
          }
        }
      }
    }
    coefs->normalize(factor); // Normalize the coefs by number of samples

    // Put the coefs of this point back into the list
    coefsList[i] = coefs;
  }
}

MeshSHCalculator::~MeshSHCalculator() {
  for (int i = 0; i < coefsList.size(); i++) {
    delete coefsList[i];
  }
}

const std::vector<SHCoefs *> &MeshSHCalculator::getCoefsList() { return coefsList; }