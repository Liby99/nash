#include "object/cube.h"

using namespace nash;

Cube::Cube() : Mesh() {
  indices = nanogui::MatrixXu(3, 12);
  indices.col(0) << 0, 1, 2;
  indices.col(1) << 2, 3, 0;
  indices.col(2) << 4, 5, 6;
  indices.col(3) << 6, 7, 4;
  indices.col(4) << 8, 9, 10;
  indices.col(5) << 10, 11, 8;
  indices.col(6) << 12, 13, 14;
  indices.col(7) << 14, 15, 12;
  indices.col(8) << 16, 17, 18;
  indices.col(9) << 18, 19, 16;
  indices.col(10) << 20, 21, 22;
  indices.col(11) << 22, 23, 20;

  positions = MatrixXf(3, 24);
  positions.col(0) << -1, -1, -1;
  positions.col(1) << 1, -1, -1;
  positions.col(2) << 1, 1, -1;
  positions.col(3) << -1, 1, -1;
  positions.col(4) << -1, -1, 1;
  positions.col(5) << 1, -1, 1;
  positions.col(6) << 1, 1, 1;
  positions.col(7) << -1, 1, 1;
  positions.col(8) << -1, -1, -1;
  positions.col(9) << -1, -1, 1;
  positions.col(10) << -1, 1, 1;
  positions.col(11) << -1, 1, -1;
  positions.col(12) << 1, -1, -1;
  positions.col(13) << 1, -1, 1;
  positions.col(14) << 1, 1, 1;
  positions.col(15) << 1, 1, -1;
  positions.col(16) << -1, 1, -1;
  positions.col(17) << -1, 1, 1;
  positions.col(18) << 1, 1, 1;
  positions.col(19) << 1, 1, -1;
  positions.col(20) << -1, -1, -1;
  positions.col(21) << -1, -1, 1;
  positions.col(22) << 1, -1, 1;
  positions.col(23) << 1, -1, -1;

  normals = MatrixXf(3, 24);
  normals.col(0) << 0, 0, -1;
  normals.col(1) << 0, 0, -1;
  normals.col(2) << 0, 0, -1;
  normals.col(3) << 0, 0, -1;
  normals.col(4) << 0, 0, 1;
  normals.col(5) << 0, 0, 1;
  normals.col(6) << 0, 0, 1;
  normals.col(7) << 0, 0, 1;
  normals.col(8) << -1, 0, 0;
  normals.col(9) << -1, 0, 0;
  normals.col(10) << -1, 0, 0;
  normals.col(11) << -1, 0, 0;
  normals.col(12) << 1, 0, 0;
  normals.col(13) << 1, 0, 0;
  normals.col(14) << 1, 0, 0;
  normals.col(15) << 1, 0, 0;
  normals.col(16) << 0, 1, 0;
  normals.col(17) << 0, 1, 0;
  normals.col(18) << 0, 1, 0;
  normals.col(19) << 0, 1, 0;
  normals.col(20) << 0, -1, 0;
  normals.col(21) << 0, -1, 0;
  normals.col(22) << 0, -1, 0;
  normals.col(23) << 0, -1, 0;
}
