#version 410

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

uniform mat4 redCoefs;
uniform mat4 greenCoefs;
uniform mat4 blueCoefs;

float getChannel(mat4 m, vec3 n) {
  vec4 nb = vec4(n, 1);
  return dot(nb, m * nb);
}

void main() {
  vec3 n = normalize(fragNormal);
  n = vec3(-n.x, -n.z, n.y);
  float r = getChannel(redCoefs, n);
  float g = getChannel(greenCoefs, n);
  float b = getChannel(blueCoefs, n);
  finalColor = vec4(r / 3, g / 3, b / 3, 1);
}