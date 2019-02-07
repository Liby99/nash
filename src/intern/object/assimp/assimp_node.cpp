#include "object/assimp/assimp_node.h"

using namespace nash;

AssimpNode::AssimpNode(const std::string & name) : Object(), name(name) {
  
}

const std::string & AssimpNode::getName() {
  return name;
}

void AssimpNode::addMesh(AssimpMesh & mesh) {
  meshes[mesh.getName()] = &mesh;
  mesh.setParent(*this);
}

void AssimpNode::addChild(AssimpNode & node) {
  nodes[node.getName()] = &node;
  node.setParent(*this);
}

AssimpMesh & AssimpNode::getMesh(const std::string & name) {
  return *(meshes[name]);
}

AssimpNode & AssimpNode::getNode(const std::string & name) {
  return *(nodes[name]);
}
