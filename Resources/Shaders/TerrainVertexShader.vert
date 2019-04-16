#version 410

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
} matrices;

out vData
{
    vec3 FragPos;
} vertex;

void main() {
    gl_Position = matrices.projection * matrices.view * matrices.model * vec4(vp, 1.0);
    vertex.FragPos = vec3(matrices.model * vec4(vp, 1.0));
}