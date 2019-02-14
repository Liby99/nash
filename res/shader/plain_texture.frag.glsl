#version 410

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform sampler2D tex;

out vec4 finalColor;

void main() {
  finalColor = vec4(vec3(texture(tex, fragTexCoord)), 0.5f);
}
