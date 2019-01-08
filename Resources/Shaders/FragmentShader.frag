#version 410

out vec4 color;

in vec3 fragmentColor;

void main() {
    color = vec4(fragmentColor, 1.0);
}