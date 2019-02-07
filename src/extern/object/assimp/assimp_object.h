#ifndef ASSIMP_OBJECT_H
#define ASSIMP_OBJECT_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "object/object.h"
#include "object/assimp/assimp_node.h"
#include "object/assimp/assimp_mesh.h"

namespace nash {
  class AssimpObject : public Object {
  public:
    AssimpObject(const std::string & filename);
    ~AssimpObject();
    AssimpNode & getRootNode();
  private:
    AssimpNode * root;
    std::vector<AssimpMesh *> meshes;
    void processScene(const aiScene * scene);
    AssimpNode * parseAssimpNode(const aiNode * assimpNode);
  };
}

#endif
