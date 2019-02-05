#version 410

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

layout(std140, binding = 1) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

out vec3 fragmet_color;

void main() {
    gl_Position = vec4(vp, 1.0);
    fragmet_color = normal;
}