#version 410

out vec4 color;
in vec3 fragment_color;

void main() {
    color = vec4(fragment_color, 1.0);
}