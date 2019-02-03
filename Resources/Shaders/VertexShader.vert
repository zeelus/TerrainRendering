#version 410

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;

uniform mat4 mvp;

out vec3 fragmet_color;

void main() {
    gl_Position = mvp * vec4(vp, 1.0);
    fragmet_color = normal;
}