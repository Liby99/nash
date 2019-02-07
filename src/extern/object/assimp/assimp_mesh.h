#ifndef ASSIMP_MESH_H
#define ASSIMP_MESH_H

#include <assimp/scene.h>
#include "object/mesh.h"

namespace nash {
  class AssimpMesh : public Mesh {
  public:
    AssimpMesh(const aiMesh * mesh);
    const std::string & getName();
    
    // void render() {
    //   std::cout << "render from mesh asdfasdafds" << std::endl;
    //   Mesh::render();
    // }
    
  private:
    std::string name;
    void loadName(const aiMesh * mesh);
    void processMesh(const aiMesh * mesh);
  };
}

#endif