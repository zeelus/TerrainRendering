#version 410

out vec4 color_out;

layout (std140) uniform PointLight
{
    vec4 position;
    vec3 lightColor;
    float r;
};

in vec3 Normal;
in vec3 VertexPosition;

void main() {
    vec3 lightPos = vec3(position);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - VertexPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 ambient = vec3(0.1, 0.1, 0.1);

    vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);

    color_out = vec4(result, 1.0);
}