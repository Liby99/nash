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

vec4 getShadowCoef(int x, int y) {

}

float getChannel(vec4 s1, vec4 s2, vec4 s3, vec4 s4, float[16] coefs) {
  float c1 = dot(s1, vec4(coefs[0], coefs[1], coefs[2], coefs[3]));
  float c2 = dot(s2, vec4(coefs[4], coefs[5], coefs[6], coefs[7]));
  float c3 = dot(s3, vec4(coefs[8], coefs[9], coefs[10], coefs[11]));
  float c4 = dot(s4, vec4(coefs[12], coefs[13], coefs[14], coefs[15]));
  return c1 + c2 + c3 + c4;
}

void main() {

  // Basic property
  mat4 mvp = viewPersp * model;
  gl_Position = mvp * vec4(position, 1);
  fragPosition = vec3(model * vec4(position, 1));
  fragNormal = vec3(transpose(inverse(model)) * vec4(normal, 0));
  fragTexCoord = texCoord;

  // Calculate the dot product
  vec2 xy = objShadowCoefIndex;
  vec4 s1 = texture(objShadowCoefSampler, xy);
  vec4 s2 = texture(objShadowCoefSampler, vec2(xy.y + 1, xy.x));
  vec4 s3 = texture(objShadowCoefSampler, vec2(xy.y + 2, xy.x));
  vec4 s4 = texture(objShadowCoefSampler, vec2(xy.y + 3, xy.x));
  color.r = getChannel(s1, s2, s3, s4, redEnvCoef);
  color.g = getChannel(s1, s2, s3, s4, greenEnvCoef);
  color.b = getChannel(s1, s2, s3, s4, blueEnvCoef);
}