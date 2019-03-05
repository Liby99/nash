#version 410

#define PI 3.1415926535897932384626433832795f

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

uniform float redEnvCoefs[25];
uniform float greenEnvCoefs[25];
uniform float blueEnvCoefs[25];

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
  return 0.546274 * (n.x * n.x - n.y * n.y);
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

float sh4n4(vec3 n) {
  // 0.75 * sqrt(35/pi) * x * y * (x^2-y^2)
  return 2.503343 * n.x * n.y * (n.x * n.x - n.y * n.y);
}

float sh4n3(vec3 n) {
  // -0.75 * sqrt(35/(2pi)) * y * z * (3x^2-y^2)
  return -1.770131 * n.y * n.z * (3.0 * n.x * n.x - n.y * n.y);
}

float sh4n2(vec3 n) {
  // 0.75 * sqrt(5/pi) * x * y * (7z^2-1)
  return 0.946175 * n.x * n.y * (7.0 * n.z * n.z - 1.0);
}

float sh4n1(vec3 n) {
  // -0.75 * sqrt(5/(2pi)) * y * z * (7z^2-3)
  return -0.669047 * n.y * n.z * (7.0 * n.z * n.z - 3.0);
}

float sh40(vec3 n) {
  // 3/16 * sqrt(1/pi) * (35z^4-30z^2+3)
  float z2 = n.z * n.z;
  return 0.105786 * (35.0 * z2 * z2 - 30.0 * z2 + 3.0);
}

float sh4p1(vec3 n) {
  // -0.75 * sqrt(5/(2pi)) * x * z * (7z^2-3)
  return -0.669047 * n.x * n.z * (7.0 * n.z * n.z - 3.0);
}

float sh4p2(vec3 n) {
  // 3/8 * sqrt(5/pi) * (x^2 - y^2) * (7z^2 - 1)
  return 0.473087 * (n.x * n.x - n.y * n.y) * (7.0 * n.z * n.z - 1.0);
}

float sh4p3(vec3 n) {
  // -0.75 * sqrt(35/(2pi)) * x * z * (x^2 - 3y^2)
  return -1.770131 * n.x * n.z * (n.x * n.x - 3.0 * n.y * n.y);
}

float sh4p4(vec3 n) {
  // 3/16*sqrt(35/pi) * (x^2 * (x^2 - 3y^2) - y^2 * (3x^2 - y^2))
  float x2 = n.x * n.x;
  float y2 = n.y * n.y;
  return 0.625836 * (x2 * (x2 - 3.0 * y2) - y2 * (3.0 * x2 - y2));
}

float getChannel(float m[25], vec3 n) {
  float s = 0;
  s += a0h * m[0] * sh00(n);
  s += a1h * (m[1] * sh1n1(n) + m[2] * sh10(n) + m[3] * sh1p1(n));
  s += a2h * (m[4] * sh2n2(n) + m[5] * sh2n1(n) + m[6] * sh20(n) + m[7] * sh2p1(n) + m[8] * sh2p2(n));
  // s += a3h * (m[9] * sh3n3(n) + m[10] * sh3n2(n) + m[11] * sh3n1(n) + m[12] * sh30(n) + m[13] * sh3p1(n) + m[14] * sh3p2(n) + m[15] * sh3p3(n)); // Ignoring this line since a3h is just 0
  s += a4h * (m[16] * sh4n4(n) + m[17] * sh4n3(n) + m[18] * sh4n2(n) + m[19] * sh4n1(n) + m[20] * sh40(n) + m[21] * sh4p1(n) + m[22] * sh4p2(n) + m[23] * sh4p3(n) + m[24] * sh4p4(n));
  return s;
}

void main() {
  vec3 n = normalize(fragNormal);
  float r = getChannel(redEnvCoefs, n);
  float g = getChannel(greenEnvCoefs, n);
  float b = getChannel(blueEnvCoefs, n);
  finalColor = vec4(r, g, b, 1);
}