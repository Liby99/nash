#ifndef ASSIMP_NODE_H
#define ASSIMP_NODE_H

#include <map>
#include <assimp/scene.h>
#include "object/object.h"
#include "object/assimp/assimp_mesh.h"

namespace nash {
  class AssimpNode : public Object {
  public:
    AssimpNode(const std::string & name);
    const std::string & getName();
    void addMesh(AssimpMesh & mesh);
    void addChild(AssimpNode & node);
    AssimpMesh & getMesh(const std::string & name);
    AssimpNode & getNode(const std::string & name);
  private:
    std::string name;
    std::map<std::string, AssimpMesh *> meshes;
    std::map<std::string, AssimpNode *> nodes;
  };
}

#endif
