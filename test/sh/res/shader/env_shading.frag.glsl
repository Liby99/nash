#version 410

#define PI 3.1415926535897932384626433832795f

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

uniform mat4 redCoefs;
uniform mat4 greenCoefs;
uniform mat4 blueCoefs;

float a0h = 3.141593, a1h = 2.094395, a2h = 0.785398,
      a3h = 0, a4h = -0.130900, a5h = 0, a6h = 0.049087;

float sh00(vec3 n) {
  return 0.282095;
}

float sh1n1(vec3 n) {
  return -0.488603 * n.y;
}

float sh10(vec3 n) {
  return 0.488603 * n.z;
}

float sh1p1(vec3 n) {
  return -0.488603 * n.x;
}

float sh2n2(vec3 n) {
  return 1.092548 * n.x * n.y;
}

float sh2n1(vec3 n) {
  return -1.092548 * n.y * n.z;
}

float sh20(vec3 n) {
  return 0.315392 * (3 * n.z * n.z - 1);
}

float sh2p1(vec3 n) {
  return -1.092548 * n.x * n.z;
}

float sh2p2(vec3 n) {
  return 0.546274 * n.x * n.z;
}

float sh3n3(vec3 n) {
  return -0.590044 * n.y * (3.0 * n.x * n.x - n.y * n.y);
}

float sh3n2(vec3 n) {
  return 2.890611 * n.x * n.y * n.z;
}

float sh3n1(vec3 n) {
  return -0.457046 * n.y * (4.0 * n.z * n.z - n.x * n.x - n.y * n.y);
}

float sh30(vec3 n) {
  return 0.373176 * n.z * (2.0 * n.z * n.z - 3.0 * n.x * n.x - 3.0 * n.y * n.y);
}

float sh3p1(vec3 n) {
  return -0.457046 * n.x * (4.0 * n.z * n.z - n.x * n.x - n.y * n.y);
}

float sh3p2(vec3 n) {
  return 1.445306 * n.z * (n.x * n.x - n.y * n.y);
}

float sh3p3(vec3 n) {
  return -0.590044 * n.x * (n.x * n.x - 3.0 * n.y * n.y);
}

float getChannel(mat4 m, vec3 n) {
  float s = 0;
  s += m[0][0] * sh00(n);
  s += m[0][1] * sh1n1(n) + m[1][1] * sh10(n) + m[1][0] * sh1p1(n);
  s += m[0][2] * sh2n2(n) + m[1][2] * sh2n1(n) + m[2][2] * sh20(n) + m[2][1] * sh2p1(n) + m[2][0] * sh2p2(n);
  // s += m[0][3] * sh3n3(n) + m[1][3] * sh3n2(n) + m[2][3] * sh3n1(n) + m[3][3] * sh30(n) + m[3][2] * sh3p1(n) + m[3][1] * sh3p2(n) + m[3][0] * sh3p3(n);
  return s;
}

void main() {
  vec3 n = normalize(fragNormal);
  float r = getChannel(redCoefs, n);
  float g = getChannel(greenCoefs, n);
  float b = getChannel(blueCoefs, n);
  finalColor = vec4(r, g, b, 1);
}