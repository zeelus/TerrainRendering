#version 410

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
};

layout (std140) uniform PointLight
{
    vec3 position_ws;
    vec3 color;
    float r;
};


out vec3 fragmet_color;

void main() {
    gl_Position = projection * view * model * vec4(vp, 1.0);
    fragmet_color = color;
}