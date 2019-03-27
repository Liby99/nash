#version 410

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform sampler2DRect tex;
uniform int size;

out vec4 finalColor;

void main() {
  finalColor = texture(tex, fragTexCoord * size);
}
