#version 410

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;
layout(location=3) in float objShadowCoefIndex;

out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTexCoord;

// The Dot Products
out vec3 color;

// Basic
uniform mat4 model = mat4(1);
uniform mat4 viewPersp = mat4(1);

// Environment Map Related
uniform float redEnvCoef[16];
uniform float greenEnvCoef[16];
uniform float blueEnvCoef[16];

// Object Self Shadow Related
uniform samplerBuffer objShadowCoefSampler;

float getChannel(int i, float[16] coefs) {
  vec4 s0 = texelFetch(objShadowCoefSampler, i) / 8; // TODO: why is this 8
  vec4 s1 = texelFetch(objShadowCoefSampler, i + 1) / 8;
  vec4 s2 = texelFetch(objShadowCoefSampler, i + 2) / 8;
  vec4 s3 = texelFetch(objShadowCoefSampler, i + 3) / 8;

  float c0 = s0.x * coefs[0];
  float c1 = 0.4886025 * dot(s0.yzw, vec3(coefs[1], coefs[2], coefs[3]));
  float c2 = 0.6307831 * (dot(s1, vec4(coefs[4], coefs[5], coefs[6], coefs[7])) + s2.x * coefs[8]);
  float c3 = 0.746353 * (dot(s2.yzw, vec3(coefs[9], coefs[10], coefs[11]) + dot(s3, vec4(coefs[12], coefs[13], coefs[14], coefs[15]))));

  return max(0, c0 + c1 + c2 + c3);
}

void main() {

  // Basic property
  mat4 mvp = viewPersp * model;
  gl_Position = mvp * vec4(position, 1);
  fragPosition = vec3(model * vec4(position, 1));
  fragNormal = vec3(transpose(inverse(model)) * vec4(normal, 0));
  fragTexCoord = texCoord;

  // Calculate the dot product color
  int i = int(objShadowCoefIndex);
  float r = getChannel(i, redEnvCoef);
  float g = getChannel(i, greenEnvCoef);
  float b = getChannel(i, blueEnvCoef);
  color = vec3(r, g, b);
}