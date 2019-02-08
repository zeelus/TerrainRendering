#version 410

out vec4 color_out;

layout (std140) uniform PointLight
{
    vec4 position;
    vec3 color;
    float r;
} pointLight;

void main() {
    color_out = vec4(pointLight.color, 1.0);
}