#version 410

out vec4 color_out;

layout (std140) uniform PointLight
{
    vec3 position;
    vec3 color;
} pointLight;

void main() {
    color_out = vec4(pointLight.color, 1.0);
}