#version 410

out vec4 color_out;

layout (std140) uniform PointLight
{
    vec4 position;
    vec3 lightColor;
    float r;
} light;

layout (std140) uniform Matrices
{
    mat4 model;
    mat4 view;
    mat4 projection;
} matrices;

in fData
{
    vec3 Normal;
    vec3 FragPos;
} fragData;

const float shininess = 8.0;

void main() {

    //mat3 normalMatrix = transpose(inverse(mat3(matrices.model)));
    vec3 normal = fragData.Normal; //normalize(normalMatrix * fragData.Normal);

    vec3 lightDir = vec3(light.position) - fragData.FragPos;

    float brightness = dot(normal, lightDir) / (length(lightDir) * length(normal));
    brightness = clamp(brightness, 0, 1);

    vec3 ambient = vec3(0.1);
    vec3 diffuse = (brightness * light.r) * light.lightColor;

    vec3 modelColor = vec3(1.0f);

    vec3 viewDir = normalize(-(fragData.FragPos));
    vec3 halfDir = normalize(lightDir + viewDir);
    float specAngle = max(dot(halfDir, normal), 0.0);
    float specular = pow(specAngle, shininess);

    vec3 result = (ambient + diffuse + specular) * modelColor;

    color_out = vec4(result, 1.0);

}