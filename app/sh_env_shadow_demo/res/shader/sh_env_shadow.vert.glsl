#version 410

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 texCoord;
layout(location=3) in vec2 objShadowCoefIndex;

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
uniform sampler2DRect objShadowCoefSampler;

vec4 getShadowCoef(float x, float y) {
  vec4 raw = texture(objShadowCoefSampler, vec2(x, y));
  return (raw - vec4(0.5f)) * 4.0f;
}

float getChannel(vec4 s1, vec4 s2, vec4 s3, vec4 s4, float[16] coefs) {
  float c1 = s1.x * coefs[0];
  float c2 = dot(s1.yzw, vec3(coefs[1], coefs[2], coefs[3]));
  float c3 = (dot(s2, vec4(coefs[4], coefs[5], coefs[6], coefs[7])) + s3.x * coefs[8]);
  float c4 = (dot(s3.yzw, vec3(coefs[9], coefs[10], coefs[11])) + dot(s4, vec4(coefs[12], coefs[13], coefs[14], coefs[15])));
  return min(1, max(0, c1 + c2 + c3 + c4));
}

void main() {

  // Basic property
  mat4 mvp = viewPersp * model;
  gl_Position = mvp * vec4(position, 1);
  fragPosition = vec3(model * vec4(position, 1));
  fragNormal = vec3(transpose(inverse(model)) * vec4(normal, 0));
  fragTexCoord = texCoord;

  // Calculate the dot product color
  float x = objShadowCoefIndex.x + 0.5f;
  float y = objShadowCoefIndex.y + 0.5f;
  vec4 s1 = getShadowCoef(x, y);
  vec4 s2 = getShadowCoef(x, y + 1);
  vec4 s3 = getShadowCoef(x, y + 2);
  vec4 s4 = getShadowCoef(x, y + 3);
  float r = getChannel(s1, s2, s3, s4, redEnvCoef);
  float g = getChannel(s1, s2, s3, s4, greenEnvCoef);
  float b = getChannel(s1, s2, s3, s4, blueEnvCoef);
  color = vec3(r, g, b);
}