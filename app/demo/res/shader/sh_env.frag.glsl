#version 410

#define PI 3.1415926535897932384626433832795f

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

uniform float redEnvCoefs[16];
uniform float greenEnvCoefs[16];
uniform float blueEnvCoefs[16];

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

float getChannel(float m[16], vec3 n) {
  float s = 0;
  s += a0h * m[0] * sh00(n);
  s += a1h * (m[1] * sh1n1(n) + m[2] * sh10(n) + m[3] * sh1p1(n));
  s += a2h * (m[4] * sh2n2(n) + m[5] * sh2n1(n) + m[6] * sh20(n) + m[7] * sh2p1(n) + m[8] * sh2p2(n));
  s += a3h * (m[9] * sh3n3(n) + m[10] * sh3n2(n) + m[11] * sh3n1(n) + m[12] * sh30(n) + m[13] * sh3p1(n) + m[14] * sh3p2(n) + m[15] * sh3p3(n));
  return s;
}

void main() {
  vec3 n = normalize(fragNormal);
  float r = getChannel(redEnvCoefs, n);
  float g = getChannel(greenEnvCoefs, n);
  float b = getChannel(blueEnvCoefs, n);
  finalColor = vec4(r, g, b, 1);
}