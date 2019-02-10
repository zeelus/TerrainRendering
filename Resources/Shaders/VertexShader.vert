#version 410

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
} matrices;


out vec3 VertexPosition;
out vec3 Normal;


void main() {
    gl_Position = matrices.projection * matrices.view * matrices.model * vec4(vp, 1.0);
    VertexPosition = vp;
    Normal = normal;
}