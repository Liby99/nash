
#include <nash/nash.h>
#include <adhoc/raytrace/box_tree_node.h>


using namespace nash;

BoxTreeNode::BoxTreeNode(const MatrixXu &indices,
                         const BoxTreeMesh *boxTreeMesh) :
    indices(indices), boxTreeMesh(boxTreeMesh) {
  left = nullptr;
  right = nullptr;
  // create bounding box
  std::vector<Vector3f> vertices;
  for (int i = 0; i < indices.cols(); i++) {
    Vector3u currTri = indices.col(i);
    vertices.push_back(boxTreeMesh->getMesh().getPositions().col(currTri[0]));
    vertices.push_back(boxTreeMesh->getMesh().getPositions().col(currTri[1]));
    vertices.push_back(boxTreeMesh->getMesh().getPositions().col(currTri[2]));
  }
  boundingBox = new BoundingBox(vertices);
  int currSize = indices.cols();
  //TODO: delete this when finalized
  //fprintf(stderr, "======Current indices size: %d\n", currSize);
  if (indices.cols() > boxTreeMesh->leafSize) {
    partition();
  } else {
    // TODO
    triangle = new Triangle(vertices[0], vertices[1], vertices[2]);
  }
}

bool BoxTreeNode::intersect(const Ray &ray, Intersection &intersection) {
  // leaf node
  bool ret = false;
  if (isLeaf()) {
    ret = triangle->intersect(ray, intersection);
    // TODO
    return ret;
  }

  // Not a leaf node, check if intersect self
  bool result = boundingBox->intersect(ray, intersection);
  if (result) {
    // test children
    if (left) {
      ret = left->intersect(ray, intersection);
    }
    if (right) {
      ret = (ret || right->intersect(ray, intersection));
    }
  }
  return ret;
}

bool BoxTreeNode::isLeaf() const {
  return left == nullptr && right == nullptr;
}

void BoxTreeNode::partition() {
  Vector3f extents = boundingBox->getExtents();
  int dim;
  float max = std::max(std::max(extents[0], extents[1]), extents[2]);
  for (dim = 0; dim < 2; dim++) {
    if (fabs(extents[dim] - max) < 1e-10) {
      break;
    }
  }

  Vector3f anchor = boundingBox->getCenter();
  //float leftCoord = anchor[dim] - extents[dim];
  //float rightCoord = anchor[dim] - extents[dim];

  // partition along 'dim' axis
  MatrixXu leftIndices(3, 0);
  MatrixXu rightIndices(3, 0);

  for (int i = 0; i < indices.cols(); i++) {

    Vector3u currTri = indices.col(i);
    std::vector<Vector3f> triangle(3);
    Vector3f center(0, 0, 0);
    for (int j = 0; j < 3; j++) {
      triangle[j] = boxTreeMesh->getMesh().getPositions().col(currTri[j]);
      center += triangle[j];
    }
    center /= 3;

    //TODO: delete this when finalized
    //if (i == 0 || i == 1) {
    //  fprintf(stderr, "dim = %d\nCurrent anchor is:(%f,%f,%f) with extent(%f,"
    //                  "%f,%f);\n "
    //                  "with the triangle "
    //                  "center: (%f,%f,%f)\n", dim, anchor[0], anchor[1],
    //          anchor[2],
    //          extents[0], extents[1], extents[2],
    //          center[0], center[1], center[2]);
    //}
    // the center of this triangle is on the left side
    if (center[dim] < anchor[dim]) {
      leftIndices.conservativeResize(NoChange, leftIndices.cols() + 1);
      leftIndices.col(leftIndices.cols() - 1) = currTri;
    } else {
      rightIndices.conservativeResize(NoChange, rightIndices.cols() + 1);
      rightIndices.col(rightIndices.cols() - 1) = currTri;
    }
  }

  // build children
  if (leftIndices.cols() == 0 || rightIndices.cols() == 0) {
    //TODO: delete this when finalized
    //fprintf(stderr, "one of indices is zero\n");
    // suboptimal partition
    int count = indices.cols();
    int leftCount = count / 2;
    int rightCount = count - leftCount;
    leftIndices = MatrixXu(3, leftCount);
    rightIndices = MatrixXu(3, rightCount);
    //TODO: delete this when finalized
    //fprintf(stderr, "LeftCount %d, RightCount %d\n", leftCount, rightCount);
    int i = 0;
    for (int j = 0; j < leftCount; j++) {
      leftIndices.col(j) = indices.col(i);
      i++;
    }
    for (int j = 0; j < rightCount; j++) {
      rightIndices.col(j) = indices.col(i);
      i++;
    }
  }
  left = new BoxTreeNode(leftIndices, boxTreeMesh);
  right = new BoxTreeNode(rightIndices, boxTreeMesh);


}

